#include "custom_shell.h"

/**
 * custom_getline - Read a line of input from the user
 * @input_buffer: The input buffer to store the line
 * @max_buffer_length: The maximum length of the input buffer
 * Return: The number of characters read, or -1 on error
 */
ssize_t custom_getline(char *input_buffer, size_t max_buffer_length)
{
    static char internal_buffer[MAX_CMD_LENGTH];
    static size_t buffer_position = 0;
    static size_t buffer_size = 0;
    size_t char_count = 0;
    char current_char;

    while (char_count < max_buffer_length - 1)
    {
        if (buffer_position >= buffer_size)
        {
            buffer_size = read(STDIN_FILENO, internal_buffer, sizeof(internal_buffer));
            if (buffer_size <= 0)
                return (buffer_size);
            buffer_position = 0;
        }
        current_char = internal_buffer[buffer_position++];
        input_buffer[char_count++] = current_char;
        if (current_char == '\n')
            break;
    }

    input_buffer[char_count] = '\0';
    return (char_count);
}
