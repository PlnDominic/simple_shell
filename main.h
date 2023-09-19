#ifndef CUSTOM_SHELL_H
#define CUSTOM_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <pwd.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 64
#define MAX_ENV_VARS 1000
#define PATH_SEPARATOR ":"

void execute_custom_command(const char * const arguments[]);
int custom_strcmp(char *str1, char *str2);
int custom_strlen(const char *str);
ssize_t custom_getline(char *input, size_t max_length);
char *get_full_executable_path(const char *command);
char *custom_strcpy(char *destination, const char *source);
char *custom_strcat(char *destination, const char *source);
void handle_exit_command(char **input);
int custom_atoi(char *str);
int custom_strncmp(const char *str1, const char *str2, size_t n);
extern char **custom_environment;
int set_custom_environment_variable(char **args);
int unset_custom_environment_variable(char **args);
char *get_full_executable_path(const char *command);
void print_custom_environment(void);
int change_working_directory(char *path);

#endif
