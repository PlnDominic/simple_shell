#include "shell.h"

/**
 * interactive - if in interactive mode return true
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checking if character is a delimeter
 * @h: the character to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char h, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == h)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @s: The character to input
 * Return: 1 if s is alphabetic, 0 otherwise
 */

int _isalpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - String to interger
 * @c: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *c)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0; c[j] != '\0' && flag != 2; j++)
	{
		if (c[j] == '-')
			sign *= -1;

		if (c[j] >= '0' && c[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (c[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
