#include "shell.h"
#include "commands.c"

typedef int (*functionCall)(int,char*[]);

typedef struct {
    const char *keyword;
    functionCall function;
} Keyword;

void cleanup(int n_args, char* arguments[]){
    for(int i=0; i<n_args; i++)
        free(arguments[i]);
    if(DEBUG) printf("cleaned up %d arguments\n", n_args);
}

int close(int args, char* arguments[]){
    printf("goodbye\n");
    cleanup(args+1, arguments);
    exit(0);
}

static const Keyword keywords[] = {
    { "exit", &close },
    { "connect",  &connect},
    { "disconnect", &disconnect },
    { "help",  &help},
    // { "SELECT", CMD_DB },
    // { "INSERT", CMD_DB },
    // { "CREATE", CMD_DB },
};

functionCall lookup(const char *token) {
    for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++)
        if (strcasecmp(token, keywords[i].keyword) == 0)
            return keywords[i].function;
    return &unknown_command;
}

char* duplicate_string(const char* string){
    size_t len = strlen(string);
    char* ret = (char*) malloc(len*sizeof(char));
    char* aux = ret;
    for(int i=0; i < len; i++) {*aux = string[i]; aux++;}
    *aux = '\0';
    return ret;
}

int parse_line(char* tokens[MAX_TOKENS]){
    char input[MAX_INPUT];
    fgets(input, MAX_INPUT, stdin);
    int n_args = 0;
    if(strlen(input) <= 0) return 0;
    char* token = strtok(input, " \t\n");
    for(; token != NULL;){
        tokens[n_args++] = duplicate_string(token);
        token = strtok(NULL, " \t\n");
    }
    return n_args;
}


int do_shell(const char* prompt){
    for(;;){
        fputs(prompt, stdout);
        char* arguments[MAX_TOKENS];
        int tokens = parse_line(arguments);
        if(tokens == 0) continue;
        if((*lookup(arguments[0]))(tokens-1, arguments) == -1) continue;
        cleanup(tokens, arguments);
    }
}

int main(int argc, char const *argv[]){
    return do_shell(PROMPT);
}