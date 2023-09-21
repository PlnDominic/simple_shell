#ifndef DR_SHELL_H
#define DR_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Function prototypes */
void dr_signal_handler(int signal);

/* Global variables */
extern char **environ;

#endif /* SHELL_H */
