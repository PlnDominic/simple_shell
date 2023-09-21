#include "dr_shell.h"
/**
 * our_strcat - concatenates two strings
 * @final_str: string to append to
 * @str_to: string to add
 *
 * Return: a pointer to the resulting string
 */
char *dr_strcat(char *dr_str, char *str_to)
{
	int i, j;

	i = 0;
	while (dr_str[i] != '\0')
		i++;

	j = 0;
	while (str_to[j] != '\0')
	{
		dr_str[i] = str_to[j];
		j++;
		i++;
	}
	dr_str[i] = '\0';

	return (final_str);
}