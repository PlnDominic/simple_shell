#include "custom_shell.h"

/**
 * display_custom_environment - Prints the current environment variables.
 */
void display_custom_environment(void)
{
    char **env_variable = custom_environment;

    while (*env_variable)
    {
        size_t variable_length = custom_strlen(*env_variable);

        write(STDOUT_FILENO, *env_variable, variable_length);
        write(STDOUT_FILENO, "\n", 1);

        env_variable++;
    }
}
