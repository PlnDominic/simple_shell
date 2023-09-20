#include "custom_shell.h"

/**
 * custom_strcat - Concatenates strings.
 *
 * @destination: The destination string to concatenate to.
 *
 * @source: The source string to concatenate.
 *
 * Return: The value of destination.
 */
char *custom_strcat(char *destination, const char *source)
{
    char *dest_pointer = destination;

    while (*dest_pointer != '\0')
    {
        dest_pointer++;
    }
    while (*source != '\0')
    {
        *dest_pointer = *source;
        dest_pointer++;
        source++;
    }
    *dest_pointer = '\0';
    return (destination);
}
