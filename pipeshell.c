#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_ARGS 10

void execute_command(char *cmd)
{
    char *args[MAX_ARGS];
    int i = 0;
    char *token = strtok(cmd, " ");
    while (token && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    if (execvp(args[0], args) == -1)
    {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

void handle_pipe(char *cmd1, char *cmd2)
{
    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execute_command(cmd1);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execute_command(cmd2);
        wait(NULL);
    }
}

int main()
{
    while (1)
    {
        char *line = readline("shell> ");
        if (!line)
            break;
        if (strlen(line) == 0)
        {
            free(line);
            continue;
        }
        add_history(line);
        
        char *cmd1 = strtok(line, "|");
        char *cmd2 = strtok(NULL, "|");
        
        if (cmd2)
            handle_pipe(cmd1, cmd2);
        else
        {
            int pid = fork();
            if (pid == 0)
                execute_command(cmd1);
            wait(NULL);
        }
        free(line);
    }
    return 0;
}

