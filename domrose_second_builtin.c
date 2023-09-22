#include "shell.h"

/**
 * my_history - Display the history list with line numbers.
 * @info: Pointer to the info_t struct.
 * Return: Always 0.
 */
int my_history(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_custom_alias - Unset a custom alias.
 * @info: Pointer to the info_t struct.
 * @alias: The alias to unset.
 * Return: 0 on success, 1 on error.
 */
int unset_custom_alias(info_t *info, char *alias)
{
    char *equal_sign, original_char;
    int result;

    equal_sign = _strchr(alias, '=');
    if (!equal_sign)
        return (1);

    original_char = *equal_sign;
    *equal_sign = '\0';

    result = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, alias, -1)));

    *equal_sign = original_char;
    return (result);
}

/**
 * set_custom_alias - Set a custom alias.
 * @info: Pointer to the info_t struct.
 * @alias: The alias to set.
 * Return: 0 on success, 1 on error.
 */
int set_custom_alias(info_t *info, char *alias)
{
    char *equal_sign;

    equal_sign = _strchr(alias, '=');
    if (!equal_sign)
        return (1);

    if (!*++equal_sign)
        return (unset_custom_alias(info, alias));

    unset_custom_alias(info, alias);
    return (add_node_end(&(info->alias), alias, 0) == NULL);
}

/**
 * print_custom_alias - Print a custom alias.
 * @node: The alias node to print.
 * Return: 0 on success, 1 on error.
 */
int print_custom_alias(list_t *node)
{
    char *equal_sign, *alias;

    if (node)
    {
        equal_sign = _strchr(node->str, '=');
        for (alias = node->str; alias <= equal_sign; alias++)
            _putchar(*alias);
        _putchar('\'');
        _puts(equal_sign + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * my_alias - Display or set custom aliases.
 * @info: Pointer to the info_t struct.
 * Return: Always 0.
 */
int my_alias(info_t *info)
{
    int i;
    char *equal_sign;
    list_t *node;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_custom_alias(node);
            node = node->next;
        }
        return (0);
    }

    for (i = 1; info->argv[i]; i++)
    {
        equal_sign = _strchr(info->argv[i], '=');
        if (equal_sign)
            set_custom_alias(info, info->argv[i]);
        else
            print_custom_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
