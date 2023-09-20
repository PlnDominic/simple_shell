#include "custom_shell.h"

/**
 * custom_strcmp - Compares two strings.
 *
 * @str1: The first string.
 *
 * @str2: The second string.
 *
 * Return: The difference between the strings.
 */
int custom_strcmp(char *str1, char *str2)
{
    while (*str1 != '\0' && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}
