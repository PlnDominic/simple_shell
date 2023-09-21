#include "my_shell.h"

/**
 * readUserInput - Reads the user input string.
 *
 * @isEOF: Return value indicating end-of-file condition.
 * Return: User input string.
 */
char *readUserInput(int *isEOF) {
    char *userInput = NULL;
    size_t bufferSize = 0;

    *isEOF = getUserInput(&userInput, &bufferSize, stdin);

    return userInput;
}
