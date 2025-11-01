#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sql.h"
#include "utils.h"

sqlite3* db;


int db_exec_safe(const char* sql)
{
  char* errmsg;

  if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
  {
    fprintf(stderr, "[\033[31mDATABASE ERROR\033[0m]: %s\n", errmsg);
    return 1;
  } else {
    return 0;
  }
}

int initdb()
{
  initpath();
  if(sqlite3_open(data_db_path, &db) != SQLITE_OK)
  {
    fprintf(stderr,"SQL-OPEN-ERROR");
    exit(1);
  }

  db_exec_safe(SQL_INIT_MAINTABLE);
  db_exec_safe(SQL_INIT_ARTISTTABLE);
  db_exec_safe(SQL_INIT_KEYWORDTABLE);
  return 0;
}

int closedb()
{
  sqlite3_close(db);
  return 0;
}
