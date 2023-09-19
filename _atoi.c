#include "my_shell.h"

/**
 * remove_shell_comments - Remove all text after
 * the '#' symbol in the input line.
 * @input_line: The input line to process.
 */
void remove_shell_comments(char *input_line)
{
    char *comment_start = strchr(input_line, '#');

    if (comment_start != NULL)
    {
        *comment_start = '\0';
    }
}

/**
 * main - Entry point for a simple shell program
 * @argument_count: The number of arguments passed to the program (unused)
 * @argument_vector: An array of strings containing the program name and arguments
 *
 * Return: Always 0 to indicate successful execution.
 */
int main(int __attribute__((unused)) argument_count, char *argument_vector[])
{
    char *input_line = NULL, *command, *arguments[MAX_INPUT_LENGTH];
    size_t input_length = 0;
    int num_arguments;
    char *program_name = argument_vector[0];

    if (program_name == NULL)
        program_name = argument_vector[0];
    else
        program_name++;
    while (1)
    {
        display_shell_prompt();
        if (!read_input_line(&input_line, &input_length, program_name))
            break;
        remove_shell_comments(input_line);
        if (input_line[0] == '\0')
        {
            free(input_line);
            continue;
        }
        tokenize_input_line(input_line, &command, arguments, &num_arguments);
        if (command == NULL)
            continue;
        execute_shell_command(command, arguments, num_arguments, program_name);
    }
    free(input_line);
    return (0);
}
