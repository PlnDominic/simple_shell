#ifndef DR_SHELL_H_
#define DR_SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 128
#define TOKEN_DELIMITER " \t\r\n\a"

/* Points to an array of pointers to strings referred to as the "environment" */
extern char **environment;

/**
 * A struct that holds essential runtime data for the shell.
 */
typedef struct ShellData {
    char **arguments;
    char *userInput;
    char **tokens;
    int status;
    int commandCounter;
    char **environmentVariables;
    char *processID;
} ShellData;

/**
 * A struct to create a linked list for separators.
 */
typedef struct SeparatorList {
    char separator;
    struct SeparatorList *next;
} SeparatorList;

/**
 * A struct to create a linked list for storing command lines.
 */
typedef struct LineList {
    char *line;
    struct LineList *next;
} LineList;

/**
 * A struct to create a linked list for storing variables.
 */
typedef struct VariableList {
    int variableLength;
    char *value;
    int valueLength;
    struct VariableList *next;
} VariableList;

/**
 * A struct for defining built-in commands.
 */
typedef struct Builtin {
    char *name;
    int (*function)(ShellData *shellData);
} Builtin;

/* Function prototypes for linked list manipulation */
SeparatorList *addSeparatorNodeEnd(SeparatorList **head, char separator);
void freeSeparatorList(SeparatorList **head);
LineList *addLineNodeEnd(LineList **head, char *line);
void freeLineList(LineList **head);
VariableList *addVariableNode(VariableList **head, int variableLength, char *variable, int valueLength);
void freeVariableList(VariableList **head);

/* Function prototypes for string manipulation */
char *stringConcatenate(char *destination, const char *source);
char *stringCopy(char *destination, char *source);
int stringCompare(char *s1, char *s2);
char *stringFindCharacter(char *s, char character);
int stringSpan(char *s, char *accept);

/* Function prototypes for memory management */
void memoryCopy(void *newPointer, const void *pointer, unsigned int size);
void *memoryReallocate(void *pointer, unsigned int oldSize, unsigned int newSize);
char **reallocateDoublePointer(char **pointer, unsigned int oldSize, unsigned int newSize);

/* Function prototypes for string operations */
char *stringDuplicate(const char *s);
int stringLength(const char *s);
int compareCharacters(char str[], const char *delimiter);
char *stringTokenize(char str[], const char *delimiter);
int isDigit(const char *s);

/* Function prototypes for error checking and reporting */
int hasRepeatedCharacter(char *input, int index);
int hasSyntaxErrorInSeparator(char *input, int index, char lastSeparator);
int findFirstNonSpaceCharacter(char *input, int *index);
void printSyntaxError(ShellData *shellData, char *input, int index, int isError);
int checkSyntaxErrors(ShellData *shellData, char *input);

/* Function prototypes for shell loop and input processing */
char *removeComments(char *input);
void runShellLoop(ShellData *shellData);
char *readUserInput(int *isEOF);

/* Function prototypes for splitting commands */
char *swapCharacters(char *input, int isSwap);
void addNodesToSeparatorsAndLines(SeparatorList **separatorList, LineList **lineList, char *input);
void goToNextSeparatorAndLine(SeparatorList **separatorList, LineList **lineList, ShellData *shellData);
int splitCommands(ShellData *shellData, char *input);
char **splitInputLine(char *input);

/* Function prototypes for variable replacement */
void checkEnvironmentVariables(VariableList **list, char *input, ShellData *shellData);
int checkVariables(VariableList **list, char *input, char *string, ShellData *shellData);
char *replaceInputWithVariables(VariableList **head, char *input, char *newInput, int newLength);
char *replaceVariables(char *input, ShellData *shellData);

/* Function prototypes for reading lines from input */
void copyLine(char **linePointer, size_t *size, char *buffer, size_t length);
ssize_t readInputLine(char **linePointer, size_t *size, FILE *stream);

/* Function prototype for executing shell commands */
int isCurrentDirectory(char *path, int *index);
char *findExecutablePath(char *command, char **environmentVariables);
int isExecutable(ShellData *shellData);
int checkCommandError(char *directory, ShellData *shellData);
int executeShellCommand(ShellData *shellData);

/* Function prototypes for working with environment variables */
char *getEnvironmentVariable(const char *name, char **environmentVariables);
int executeEnvironmentCommand(ShellData *shellData);

/* Function prototypes for working with built-in commands */
void changeDirectoryDot(ShellData *shellData);
void changeDirectoryTo(ShellData *shellData);
void changeDirectoryPrevious(ShellData *shellData);
void changeDirectoryToHome(ShellData *shellData);
int changeDirectoryShell(ShellData *shellData);

/* Function prototypes for finding and executing built-in commands */
int (*findBuiltInCommand(char *command))(ShellData *shellData);
int exitShell(ShellData *shellData);

/* Function prototypes for standard library utility */
int getLength(int number);
char *integerToString(int number);
int stringToInteger(char *string);

/* Function prototypes for handling shell errors */
char *concatenateForChangeDirectoryError(ShellData *shellData, char *currentDirectory, char *targetDirectory, char *errorMessage);
char *getChangeDirectoryError(ShellData *shellData);
char *getNotFoundError(ShellData *shellData);
char *getExitError(ShellData *shellData);

/* Function prototypes for handling various shell errors */
char *getAliasError(char **arguments);
char *getEnvironmentError(ShellData *shellData);
char *getSyntaxError(char **arguments);
char *getPermissionError(char **arguments);
char *getPathError126(ShellData *shellData);

/* Function prototype for getting shell errors */
int getShellError(ShellData *shellData, int evaluation);

/* Function prototype for handling SIGINT signal */
void handleSIGINT(int signal);

/* Function prototypes for providing help */
void provideEnvironmentHelp();
void provideSetEnvironmentHelp();
void provideUnsetEnvironmentHelp();
void provideGeneralHelp();
void provideExitHelp();

/* Function prototypes for more help topics */
void provideHelp();
void provideAliasHelp();
void provideChangeDirectoryHelp();

/* Function prototype for accessing help information */
int accessHelp(ShellData *shellData);

#endif
