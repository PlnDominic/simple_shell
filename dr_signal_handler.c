#include "dr_shell.h"
#include <unistd.h>

/**
 * _strlen - Calculates the length of a string.
 * @str: The input string.
 * Return: The length of the string.
 */
size_t _strlen(const char *str)
{
	size_t len = 0;

	while (str && str[len])
		len++;

	return (len);
}

/**
 * signal_handler - Handles signals for Ctrl+C.
 * @signal: The signal number.
 */
void signal_handler(int signal)
{
	(void)signal; // Unused parameter warning

	char *prompt = "\n$ ";
	size_t prompt_len = _strlen(prompt);

	if (write(STDOUT_FILENO, prompt, prompt_len) == -1)
		perror("write");
}

int main(void)
{
	signal(SIGINT, signal_handler);

	while (1)
	{
		// Your shell code here

		// For example, you can use fgets to read user input
		char buffer[1024];
		write(STDOUT_FILENO, "$ ", 2);
		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			perror("fgets");
			break;
		}

		// Process user input

		// For demonstration purposes, we'll just print what the user entered
		printf("You entered: %s", buffer);
	}

	return (0);
}
