#define PATH_BUF_SIZE 128

extern char* data_path;
extern char* data_db_path;
extern char* data_save_path;

int initpath(void);
void freepath(void);
void cleanall(void);
__attribute__((noreturn)) void cleanall_exit(int exit_code);
void cleanall_s(int signal);
