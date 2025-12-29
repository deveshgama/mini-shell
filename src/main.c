#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

void tokenize(char *input, char **args) {
    int i = 0;
    char *token = strtok(input, " \t\n");

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

int main() {
    char input[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        printf("mini-shell> ");
        fflush(stdout);

        if (!fgets(input, MAX_LINE, stdin)) {
            printf("\n");
            break;
        }

        tokenize(input, args);

        if (args[0] == NULL)
            continue;

        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            perror("exec failed");
            exit(1);
        } 
        else if (pid > 0) {
            wait(NULL);
        } 
        else {
            perror("fork failed");
        }
    }
    return 0;
}
