#include "custom_shell.h"

/**
 * execute_command_in_custom_path - Execute a command found
 * in the PATH environment variable.
 * @shell_name: The name of the custom shell program.
 * @command: The command to search for and execute.
 * @arguments: An array of arguments for the command.
 */
void execute_command_in_custom_path(const char *shell_name,
                                    const char *command, char *arguments[])
{
    char *command_path = NULL, *path_copy, *path_token, *path = find_custom_path("PATH");
    int command_not_found = 1;
    size_t path_length, command_length;

    if (path == NULL)
    {
        return;
    }
    path_copy = duplicate_string(path);
    if (path_copy == NULL)
    {
        return;
    }
    path_token = strtok(path_copy, ":");
    while (path_token != NULL)
    {
        path_length = custom_strlen(path_token);
        command_length = custom_strlen(command);
        command_path = (char *)malloc(path_length + command_length + 2);
        if (command_path == NULL)
        {
            perror(shell_name);
            free(path_copy);
            return;
        }
        copy_custom_string(command_path, path_token);
        custom_strcat(command_path, "/");
        custom_strcat(command_path, command);
        if (access(command_path, X_OK) == 0)
        {
            run_custom_command(shell_name, command_path, arguments);
            command_not_found = 0;
            free(command_path);
            break;
        }
        free(command_path);
        path_token = strtok(NULL, ":");
    }
    free(path_copy);
    if (command_not_found)
    {
        perror(shell_name);
    }
}
