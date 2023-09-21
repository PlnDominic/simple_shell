#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>

/**
 * Function to handle signals, e.g., Ctrl+C
 */
void signal_handler(int signal)
{
    (void)signal;
    write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * Function to tokenize a string
 */
char **tokenize(char *input)
{
    const char *delimiters = " \n\t\r\a";
    char **tokens = malloc(sizeof(char *) * 64);
    if (!tokens)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    char *token = strtok(input, delimiters);
    while (token)
    {
        tokens[i] = strdup(token);
        if (!tokens[i])
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        i++;
        token = strtok(NULL, delimiters);
    }
    tokens[i] = NULL;
    return tokens;
}

/**
 * Function to execute a command
 */
void execute_command(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        // Child process
        if (execvp(args[0], args) == -1)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        // Parent process
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main(int argc, char **argv)
{
    signal(SIGINT, signal_handler);

    while (1)
    {
        char *input = NULL;
        size_t input_len = 0;

        if (isatty(STDIN_FILENO))
        {
            write(STDOUT_FILENO, "$ ", 2);
        }

        if (getline(&input, &input_len, stdin) == -1)
        {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        // Remove trailing newline character
        size_t input_length = strlen(input);
        if (input_length > 0 && input[input_length - 1] == '\n')
        {
            input[input_length - 1] = '\0';
        }

        // Handle exit command
        if (strcmp(input, "exit") == 0)
        {
            free(input);
            exit(EXIT_SUCCESS);
        }

        // Tokenize the input
        char **args = tokenize(input);

        // Execute the command
        if (args[0] != NULL)
        {
            execute_command(args);
        }

        // Free allocated memory
        for (int i = 0; args[i] != NULL; i++)
        {
            free(args[i]);
        }
        free(args);
        free(input);
    }

    return 0;
}
