#include "commands.h"

CurrentState* state;

int list_dbs(int args, char* arguments[]){
  if(args != 0) {printf("expecting 0 arguments\n"); return -1;}
  system(SHELLSCRIPT);
  
  //execvp("./db_files/list.dbs", NULL);

  return 0;
}

char* calculate_db_path(const char* db_name){ 
  int db_pat_len = strlen(db_name) + strlen("db_files/.db");
  char* db_path = (char*) malloc(sizeof(char)*db_pat_len);
  strcpy(db_path, "db_files/");
  strcat(db_path, db_name);
  strcat(db_path, ".db\0");
  return db_path;
}

int create_db(int args, char* arguments[]){
  if(args != 1) {printf("expecting only an argument: db_name\n"); return -1;}
  char* db_path = calculate_db_path(arguments[1]);
  
  if(state == NULL) {printf("state is not initialized\n"); return -1; }
  if(access(db_path, F_OK) == 0){printf("db %s already exists, remove it first\n", arguments[1]); return -1;} 
  state->db_fd = open(db_path, O_CREAT);
  if(state->db_fd == -1) {printf("cannot create db file\n"); return -1;}
  printf("created %s\n", arguments[1]);
  free(db_path);
}

int connect(int args, char* arguments[]){
  if(args != 1) {printf("expecting only an argument: db_name\n"); return -1;}
  printf("connecting to %s\n", arguments[1]); 

  char* db_path = calculate_db_path(arguments[1]);
  
  if(state == NULL) {printf("state is not initialized\n"); return -1; }
  printf("db_path: %s\n", db_path);
  state->db_fd = open(db_path, O_RDWR | O_APPEND);
  if(state->db_fd == -1) {printf("cannot open db file\n"); return -1;}
  free(db_path);

  state->is_db_connected = 1;
  strcpy(state->db_connected, arguments[1]);

  printf("connected to: %s\n", state->db_connected);
  return 0;
}

int disconnect(int args, char* arguments[]){
  if(args != 0) {printf("expecting 0 arguments\n"); return -1;}
  if(state == NULL) {printf("state is not initialized\n"); return -1; }
  if(!(state->is_db_connected)) {printf("you are not connected to any db\n"); return -1; }
  printf("disconnecting from %s\n", state->db_connected);

  state->is_db_connected = 0;
  close(state->db_fd);
  printf("disconnected from: %s\n", state->db_connected);
  strcpy(state->db_connected, "");
  return 0;
}

int check_current_db(int args, char* arguments[]){
  char cdb[MAX_DB_NAME];
  if(state == NULL) {printf("state is not initialized\n"); return -1; }
  if(!state->is_db_connected) {
    printf("you are not connected to any db\n");
    return -1;
  }
  strcpy(cdb, state->db_connected);
  printf("current BD: %s\n", cdb);
  return 0;
}

int create_table(int args, char* arguments[]){
  return 0;
}

int unknown_command(int args, char* arguments[]){
    printf("unknown command\n");
    return 0;
}
