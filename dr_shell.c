#include "dr_shell.h"

/**
 * freeShellData - Release memory associated with the shell data structure.
 *
 * @shellData: Shell data structure.
 */
void freeShellData(ShellData *shellData) {
    unsigned int i;

    for (i = 0; shellData->environmentVariables[i]; i++) {
        free(shellData->environmentVariables[i]);
    }

    free(shellData->environmentVariables);
    free(shellData->processID);
}

/**
 * initializeShellData - Initialize the shell data structure.
 *
 * @shellData: Shell data structure.
 * @arguments: Argument vector.
 */
void initializeShellData(ShellData *shellData, char **arguments) {
    unsigned int i;

    shellData->arguments = arguments;
    shellData->userInput = NULL;
    shellData->tokens = NULL;
    shellData->status = 0;
    shellData->commandCounter = 1;

    for (i = 0; environment[i]; i++) {
        ;
    }

    shellData->environmentVariables = malloc(sizeof(char *) * (i + 1));

    for (i = 0; environment[i]; i++) {
        shellData->environmentVariables[i] = stringDuplicate(environment[i]);
    }

    shellData->environmentVariables[i] = NULL;
    shellData->processID = integerToString(getpid());
}

/**
 * main - Entry point of the shell program.
 *
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success.
 */
int main(int argc, char **argv) {
    ShellData shellData;
    (void) argc;

    signal(SIGINT, handleSIGINT);
    initializeShellData(&shellData, argv);
    runShellLoop(&shellData);
    freeShellData(&shellData);

    if (shellData.status < 0) {
        return 255;
    }

    return shellData.status;
}
