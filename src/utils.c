#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "sql.h"
#include "utils.h"

char* data_path = NULL;
char* data_db_path = NULL;
char* data_save_path = NULL;

static char *home = NULL;


size_t mari_strlen(const char* str) {
  const char* p = str;
  while(*p)  p++;
  return p - str;
}


void cleanall(void){
  freepath();
  closedb();
}

void cleanall_exit(int exit_code) {
  cleanall();
  _exit(exit_code);
}

void cleanall_s(int signal){
  cleanall();
  fprintf(stderr,"Program Stoped\n SIGNAL: %d\n", signal);
}

void freepath(void)
{
  free(data_path);
  free(data_db_path);
  free(data_save_path);
}


int mkdir_p(const char* path, mode_t mode)
{
  char *temp = strdup(path);
  char *p = temp + strlen(home); //ignore $HOME

  while(*p == '/') {
    p++;
  }

  while(*p != '\0')
  {
    if(*p == '/'){
      *p = '\0';

      if(mkdir(temp, mode) == -1 && errno != EEXIST){
        perror("mkdir");
        return -1;
      }else {
        *p = '/';
      }
    }
    p++;
  }

  free(temp);
  return 0;
}

int initpath(void) 
{
  home = getenv("HOME");

  if (!home) {
    fprintf(stderr, "Error: $HOME is not set\n");
    return 1;
  }

  if(asprintf(&data_path, "%s/.local/share/mtuneup", home) == -1) goto err;
  if(asprintf(&data_db_path, "%s/.local/share/mtuneup/database.db", home) == -1) goto err;
  if(asprintf(&data_save_path, "%s/.local/share/mtuneup/music", home) == -1) goto err;

  mkdir_p(data_path, 0755);
  mkdir_p(data_save_path, 0755);

  printf("\n [PATH]\n==> %s\n==> %s\n==> %s\n",data_path,data_db_path,data_save_path);
  return 0;

  err:
    freepath();
    return 1;
}

int getvideo(const char* url, const char* title)
{
  char* path;
  if(asprintf(&path, "%s/%s", data_save_path, title) == -1) {
    perror("asprintf");
    return -1;
  }
  char *const yt_argv[] = { "yt-dlp", "-x", "--audio-format", "mp3", "-o", path, (char*) url};

  int status;
  pid_t pid = fork();

  switch (pid) {
    case -1:
      perror("fork");
      free(path);
      cleanall_exit(1);
    case 0:
      signal(SIGINT, SIG_DFL);
      execvp(yt_argv[0], yt_argv);
      perror("execvp failed");
      _exit(1);
    default:
      waitpid(pid, &status, WUNTRACED);
      if(WIFEXITED(status)){
        int code = WEXITSTATUS(status);
        if(code == 0) {
          return 0;
        } else {
          fprintf(stderr, "yt-dlp error.....");
          return -1;
        }
      }
      else if(WIFSIGNALED(status)){
        fprintf(stderr, "Who killed yt-dlp.\nyt-dlp killed by signal...\n");
        free(path);
        cleanall_exit(1);
        return -1;
      }
  }
  free(path);
  return -1;
}
