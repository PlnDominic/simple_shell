#ifndef DR_SHELL_H
#define DR_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stddef.h>

extern char **environ;

#define TOK_DELIM " \t\r\n\a\""

/* Prototypes */
char **split_line(char *line);
void shell_no_interactive(void);
char *read_line(void);
int execute_args(char **args);
int new_process(char **args);
void shell_interactive(void);
char *read_stream(void);

/* Builtin Functions */
int dr_cd(char **args);
int dr_env(char **args);
int dr_exit(char **args);
void handle_exit(char **input);

#endif