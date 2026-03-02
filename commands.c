int connect(int args, char* arguments[]){
    if(args != 1) {printf("expecting only an argument: db_name\n"); return -1;}
    printf("connecting to %s\n", arguments[1]);
    return 0;
}

int disconnect(int args, char* arguments[]){
    if(args != 1) {printf("expecting only an argument: db_name\n"); return -1;}
    printf("disconnecting from %s\n", arguments[1]);
    return 0;
}

int unknown_command(int args, char* arguments[]){
    printf("unknown command\n");
    return 0;
}