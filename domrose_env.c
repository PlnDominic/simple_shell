#include "shell.h"

/**
 * my_env - Print the current environment variables.
 * @info: Pointer to the info_t struct.
 * Return: Always 0.
 */
int my_env(info_t *info)
{
    print_list_str(info->env);
    return (0);
}

/**
 * get_env_variable - Get the value of an environment variable.
 * @info: Pointer to the info_t struct.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *get_env_variable(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *s;

    while (node)
    {
        s = starts_with(node->str, name);
        if (s && *s)
            return (s);
        node = node->next;
    }
    return (NULL);
}

/**
 * my_setenv - Set or modify an environment variable.
 * @info: Pointer to the info_t struct.
 * Return: Always 0.
 */
int my_setenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * my_unsetenv - Remove an environment variable.
 * @info: Pointer to the info_t struct.
 * Return: Always 0.
 */
int my_unsetenv(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i < info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * populate_env_list - Populate the environment linked list.
 * @info: Pointer to the info_t struct.
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}
