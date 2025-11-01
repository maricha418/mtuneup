#include <sqlite3.h>

#include "utils.h"

#define SQL_INIT_MAINTABLE \
  "CREATE TABLE IF NOT EXISTS Main ( " \
  "  ID INTEGER PRIMARY KEY AUTOINCREMENT," \
  "  title TEXT NOT NULL," \
  "  url TEXT," \
  "  path TEXT," \
  "  comment TEXT" \
  ");"

#define SQL_INIT_KEYWORDTABLE \
  "CREATE TABLE IF NOT EXISTS Keyword (" \
  "  ID INTEGER PRIMARY KEY AUTOINCREMENT," \
  "  song_id INTEGER NOT NULL," \
  "  keyword TEXT NOT NULL" \
  ");" 


#define SQL_INIT_ARTISTTABLE \
  "CREATE TABLE IF NOT EXISTS Artist (" \
  "  ID INTEGER PRIMARY KEY AUTOINCREMENT," \
  "  song_id INTEGER NOT NULL," \
  "  artist TEXT NOT NULL" \
  ");"

extern sqlite3* db;

int initdb(void);
int closedb(void);
int getnextid();
int exec_db(music_info* m);
int db_exec_safe(const char* sql);
