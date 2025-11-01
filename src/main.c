#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<signal.h>
#include<stdbool.h>
#include<sqlite3.h>

#include "sql.h"
#include "utils.h"

typedef struct {
  bool islocal;
  char* title;
  char* comment;
  int artist_c;
  char** artist;
  int keyword_c;
  char** keyword;
  char* url;
} music_info;

music_info* initmusic(void);
void addartist(music_info* minfo, const char* name);
void addkeyword(music_info* minfo, const char* name);
int chkmdata(music_info* minfo); //check music data.

music_info* initmusic(void)
{
  music_info* m = calloc(1, sizeof(music_info));
  if(!m){
    perror("calloc");
    exit(1);
  }
  m -> islocal = false;
  return m;
}

int chkmdata(music_info* minfo)
{
  
}

void addkeyword(music_info* minfo, const char* name)
{
  minfo->keyword = realloc(minfo->keyword, sizeof(char*) * (minfo->keyword_c + 1));
  if(!minfo->keyword){
    perror("realloc");
    exit(1);
  }
  minfo->keyword[minfo->keyword_c++] = strdup(name);
}

void addartist(music_info* minfo, const char* name)
{
  minfo->artist = realloc(minfo->artist, sizeof(char*) * (minfo->artist_c + 1));
  minfo->artist[minfo->artist_c++] = strdup(name);
}

int main(int argc, char* argv[])
{
  int opt;
  music_info* new_music = initmusic();

  signal(SIGINT, cleanall_s);

  while((opt = getopt(argc, argv, "hvt:a:k:c:l")) != -1)
  {
    switch(opt)
    {
      case 'h':
        printf("Usage: %s [-t TITLE] [-a ARTIST] [-k KEYWORD] [-c COMMENT] [-l] [URL]\n", argv[0]);
        return 0;

      case 't': //not null
        new_music->title = strdup(optarg);
      break;

      case 'a': //not null
        addartist(new_music, optarg);
      break;

      case 'k': //optional
        addkeyword(new_music, optarg);
      break;

      case 'c': //optional
        new_music->comment = strdup(optarg);
      break;

      case 'l':
        new_music->islocal = true;
      break;

      default:
        printf("Usage: %s [-t TITLE] [-a ARTIST] [-k KEYWORD] [-c COMMENT] [-l] [URL]\n", argv[0]);
        return 1;
    }
  }

  if(argc > optind){
    new_music->url = strdup(argv[optind]); 
  } else {
    fprintf(stderr,"[URL] dosen't exit!!!!!!\n");
    return -1;
  }

  initdb();
 // chkmdata();
  printf("==> add song data\n");


  sqlite3_close(db);
}
