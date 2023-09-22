#include "shell.h"

/**
 * change_shell - changes current directory
 *
 * @datash: data relevant
 * Return: 1 success always
 */
int cd_shell(data_shell *datash)
{
	char *i;
	int ishome, ishome2, isddash;

	i = datash->args[1];

	if (i != NULL)
	{
		ishome = _strcmp("$HOME", i);
		ishome2 = _strcmp("~", i);
		isddash = _strcmp("--", i);
	}

	if (i == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", i) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", i) == 0 || _strcmp("..", i) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}