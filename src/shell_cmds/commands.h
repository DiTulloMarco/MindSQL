#ifndef COMMANDS
#define COMMANDS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_DB_NAME 16

#define SHELLSCRIPT "\
#/bin/bash \n\
for db in `ls db_files`; do \n\
echo $db \n\
done \n\
"

typedef struct {
  char is_db_connected;
  char* db_connected;
  int db_fd;
} CurrentState;


int list_dbs(int args, char* arguments[]);
int connect(int args, char* arguments[]);
int disconnect(int args, char* arguments[]);
int check_current_db(int args, char* arguments[]);
int create_db(int args, char* arguments[]);
int create_table(int args, char* arguments[]);
int unknown_command(int args, char* arguments[]);

#endif
