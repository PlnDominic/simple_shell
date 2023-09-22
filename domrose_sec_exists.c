#include "shell.h"

/**
 **_strncpy - This copies a string
 *@dest: String destination
 *@src: the source string
 *@n: number of string copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int q)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < q - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < q)
	{
		j = i;
		while (j < q)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the begining string
 *@src: the sending string
 *@n: the amount of bytes to be sed
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		i++;
	while (src[b] != '\0' && j < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - searches a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
