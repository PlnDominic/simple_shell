#include "shell.h"

/**
 * change_shell - changes current directory
 *
 * @datash: data relevant
 * Return: 1 success always
 */
int change_shell(data_shell *datash)
{
	char *i;
	int ishome, ishome_a, isddash;

	i = datash->args[1];

	if (i != NULL)
	{
		ishome = _strcmp("$HOME", i);
		ishome_a = _strcmp("~", i);
		isddash = _strcmp("--", i);
	}

	if (i == NULL || !ishome || !ishome_a || !isddash)
	{
		change_to_home(datash);
		return (1);
	}

	if (_strcmp("-", i) == 0)
	{
		change_previous(datash);
		return (1);
	}

	if (_strcmp(".", i) == 0 || _strcmp("..", i) == 0)
	{
		change_dot(datash);
		return (1);
	}

	change_to(datash);

	return (1);
}