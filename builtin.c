#include "custom_shell.h"

/**
 * custom_exit - Exits the shell.
 * @info: A structure containing potential arguments and status.
 * 
 * Return: Exits with a given exit status (0) if info.argv[0] != "exit".
 */
int custom_exit(info_t *info)
{
    int exit_status;

    if (info->argv[1])
    {
        exit_status = custom_err_atoi(info->argv[1]);
        if (exit_status == -1)
        {
            info->status = 2;
            custom_print_error(info, "Illegal number: ");
            custom_eputs(info->argv[1]);
            custom_eputchar('\n');
            return (1);
        }
        info->error_number = exit_status;
        return (-2);
    }
    info->error_number = -1;
    return (-2);
}

/**
 * custom_change_directory - Changes the current directory of the process.
 * @info: A structure containing potential arguments and environment.
 *
 * Return: Always 0 success.
 */
int custom_change_directory(info_t *info)
{
    char *current_directory, *new_directory, buffer[1024];
    int chdir_result;

    current_directory = getcwd(buffer, 1024);
    if (!current_directory)
        custom_puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1])
    {
        new_directory = custom_get_environment_variable(info, "HOME=");
        if (!new_directory)
            chdir_result = chdir((new_directory = custom_get_environment_variable(info, "PWD=")) ? new_directory : "/");
        else
            chdir_result = chdir(new_directory);
    }
    else if (custom_strcmp(info->argv[1], "-") == 0)
    {
        if (!custom_get_environment_variable(info, "OLDPWD="))
        {
            custom_puts(current_directory);
            custom_putchar('\n');
            return (1);
        }
        custom_puts(custom_get_environment_variable(info, "OLDPWD="));
        custom_putchar('\n');
        chdir_result = chdir((new_directory = custom_get_environment_variable(info, "OLDPWD=")) ? new_directory : "/");
    }
    else
    {
        chdir_result = chdir(info->argv[1]);
    }

    if (chdir_result == -1)
    {
        custom_print_error(info, "can't cd to ");
        custom_eputs(info->argv[1]);
        custom_eputchar('\n');
    }
    else
    {
        custom_set_environment_variable(info, "OLDPWD", custom_get_environment_variable(info, "PWD="));
        custom_set_environment_variable(info, "PWD", getcwd(buffer, 1024));
    }

    return (0);
}

/**
 * custom_help - Displays a help message.
 * @info: A structure containing potential arguments.
 *
 * Return: Always 0 Success.
 */
int custom_help(info_t *info)
{
    char **argument_array;

    argument_array = info->argv;
    custom_puts("Help call works. Function not yet implemented.\n");
    if (0)
        custom_puts(*argument_array); /* Temporary unused variable workaround */

    return (0);
}
