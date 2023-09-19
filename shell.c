#include "custom_shell.h"

void run_custom_command(const char * const arguments[])
{
    pid_t child_pid;
    int child_status;

    child_pid = fork();

    if (child_pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (child_pid == 0)
    {
        if (custom_strchr(arguments[0], '/') == NULL)
        {
            char *full_executable_path = find_custom_path(arguments[0]);

            if (full_executable_path == NULL)
            {
                fprintf(stderr, "Command not found: %s\n", arguments[0]);
                exit(1);
            }
            if (execve(full_executable_path, (char * const *)arguments, custom_environment) == -1)
            {
                perror("Command execution failed");
                exit(1);
            }
        }
        else
        {
            if (execve(arguments[0], (char * const *)arguments, custom_environment) == -1)
            {
                perror("Command execution failed");
                exit(1);
            }
        }
    }
    else
    {
        waitpid(child_pid, &child_status, 0);

        if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != 0)
        {
            write(STDOUT_FILENO, "Command execution failed\n", 26);
        }
    }
}

int tokenize_custom_input(char *input, char *tokens[], int max_tokens)
{
    char *token;
    int token_count = 0;

    token = strtok(input, " ");
    while (token != NULL && token_count < max_tokens)
    {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }
    return (token_count);
}

int main(void)
{
    char user_input[MAX_CMD_LENGTH];
    size_t input_length;

    while (1)
    {
        write(STDOUT_FILENO, "custom_shell> ", 14);
        if (custom_getline(user_input, sizeof(user_input)) == -1)
        {
            perror("Error reading input");
            exit(1);
        }
        input_length = custom_strlen(user_input);

        if (input_length > 0 && user_input[input_length - 1] == '\n')
        {
            user_input[input_length - 1] = '\0';
        }
        if (custom_strcmp(user_input, "") == 0)
        {
            continue;
        }
        if (custom_strcmp(user_input, "exit") == 0)
        {
            write(STDOUT_FILENO, "Goodbye!\n", 9);
            exit(0);
        }
        if (custom_strncmp(user_input, "exit ", 5) == 0)
        {
            int exit_status = custom_atoi(user_input + 5);
            exit(exit_status);
        }
        else if (custom_strncmp(user_input, "setenv ", 7) == 0)
        {
            char *argis[3];
            int token_count = tokenize_custom_input(user_input, argis, 3);

            if (token_count != 3)
            {
                write(STDOUT_FILENO, "Usage: setenv VARIABLE VALUE\n", 29);
                continue;
            }
            if (custom_setenv(argis[1], argis[2], 1) != 0)
            {
                perror("setenv");
            }
        }
        else if (custom_strncmp(user_input, "unsetenv ", 9) == 0)
        {
            char *argis[2];
            int token_count = tokenize_custom_input(user_input, argis, 2);

            if (token_count != 2)
            {
                write(STDOUT_FILENO, "Usage: unsetenv VARIABLE\n", 25);
                continue;
            }
            if (custom_unsetenv(argis[1]) != 0)
            {
                perror("unsetenv");
            }
        }
        else if (custom_strncmp(user_input, "cd", 2) == 0)
        {
            char *path = user_input + 2;

            if (custom_strlen(path) == 0 || custom_strcmp(path, " ") == 0)
            {
                struct passwd *pw = getpwuid(getuid());
                path = pw->pw_dir;
            }
            else if (custom_strcmp(path, "-") == 0)
            {
                path = getenv("OLDPWD");

                if (path == NULL)
                {
                    write(STDERR_FILENO, "OLDPWD not set\n", 15);
                    continue;
                }
                write(STDOUT_FILENO, path, custom_strlen(path));
                write(STDOUT_FILENO, "\n", 1);
            }

            if (change_working_directory(path) != 0)
            {
                char error_message[50];
                custom_strcpy(error_message, "cd: failed to cd to ");
                custom_strcat(error_message, path);
                custom_strcat(error_message, "\n");
                write(STDERR_FILENO, error_message, custom_strlen(error_message));
            }
            continue;
        }
        else
        {
            char *argis[MAX_ARGS];
            int token_count = tokenize_custom_input(user_input, argis, MAX_ARGS);

            if (token_count == 0)
            {
                continue;
            }
            run_custom_command((const char * const *)argis);
        }
    }
    return (0);
}
