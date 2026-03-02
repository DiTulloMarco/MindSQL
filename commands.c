int connect(int args, char* arguments[]){
    if(args != 1) {printf("expecting only an argument: db_name\n"); return -1;}
    printf("connecting to %s\n", arguments[1]);
    return 0;
}

int disconnect(int args, char* arguments[]){
    if(args != 0) {printf("unexpected arguments\n"); return -1;}
    // check if connected
    printf("disconnecting from %s\n", "db_name"); // TODO: insert the connected db name
    return 0;
}

int unknown_command(int args, char* arguments[]){
    printf("unknown command\n");
    return 0;
}

int help(int args, char* arguments[]){
    printf( "connect [db_name]:             used to connect to the db_name database\n"
            "disconnect:                    disconnect from the current connected databse\n"
            "exit:                          quit MindSQL\n"
    );
    return 0;
}