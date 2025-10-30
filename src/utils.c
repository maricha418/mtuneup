#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "utils.h"

char* data_path;
char* data_db_path;
char* data_save_path;

static char *home = NULL;


size_t mari_strlen(const char* str) {
  const char* p = str;
  while(*p)  p++;
  return p - str;
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
  const char* yt-argv[] = { "yt-dlp", "-x", "--audio-format", "mp3", "-o", };

  int status;
  pid_t pid = fork();

  //signal(SIGINT, SIG_DFL);

  //memo: waitpid, WUNTRACED, execvp, WIFEXITED, WIFSIGNALED, WEXITSTATUS, signal(SIGINT, cleanall_s).
}

void cleanall_s(int signal){
  //I'm sleepy.
}

void freepath()
{
  free(data_path);
  free(data_db_path);
  free(data_save_path);
}
