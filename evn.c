#include "custom_shell.h"

/**
 * custom_print_environment - Prints the current environment.
 * @info: A structure containing potential arguments and environment.
 *
 * Return: Always 0.
 */
int custom_print_environment(info_t *info)
{
    print_list_str(info->environment);
    return (0);
}

/**
 * custom_get_environment_variable - Gets the value of an environment variable.
 * @info: A structure containing potential arguments and environment.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *custom_get_environment_variable(info_t *info, const char *name)
{
    list_t *node = info->environment;
    char *value;

    while (node)
    {
        value = starts_with(node->str, name);
        if (value && *value)
            return (value);
        node = node->next;
    }
    return (NULL);
}

/**
 * custom_set_environment_variable - Initializes a new environment variable
 *                                  or modifies an existing one.
 * @info: A structure containing potential arguments and environment.
 *
 * Return: Always 0.
 */
int custom_set_environment_variable(info_t *info)
{
    if (info->argc != 3)
    {
        custom_eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (custom_setenv(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * custom_unset_environment_variable - Removes an environment variable.
 * @info: A structure containing potential arguments and environment.
 *
 * Return: Always 0.
 */
int custom_unset_environment_variable(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        custom_eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        custom_unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * custom_populate_environment_list - Populates the environment linked list.
 * @info: A structure containing potential arguments and environment.
 *
 * Return: Always 0.
 */
int custom_populate_environment_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        custom_add_node_end(&node, environ[i], 0);
    info->environment = node;
    return (0);
}
