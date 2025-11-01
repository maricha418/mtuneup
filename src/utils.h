#include <stdbool.h>
#define PATH_BUF_SIZE 128

extern char* data_path;
extern char* data_db_path;
extern char* data_save_path;
extern char* saved_path;

int initpath(void);
void freepath(void);
int mkdir_p(const char* path, mode_t mode);
int getvideo(const char* url, int music_id);
void cleanall(void);
__attribute__((noreturn)) void cleanall_exit(int exit_code);
void cleanall_s(int signal);

#ifndef UTILS_H
#define UTILS_H
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
#endif
