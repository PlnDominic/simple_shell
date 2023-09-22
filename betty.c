#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimeter - checking delimeter
 * @s: the character to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char s, char *delim)
{
	while (*delim)
		if (*delim++ == s)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @s: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - string to an integer converter
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == '-')
			sign *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[j] - '0');
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
