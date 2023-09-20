#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ENV_VARS 100
#define MAX_INPUT_LENGTH 1024

extern int num_custom_env_vars;
extern char **custom_environment;

/**
 * struct CustomEnvVar - Structure to represent an environment variable.
 * @name: The custom environment variable name.
 * @value: The value associated with the custom environment variable.
 */
struct CustomEnvVar
{
    char *name;
    char *value;
};

void remove_comments(char *input);
void set_custom_environment_variable(const char *variable, const char *value);
void unset_custom_environment_variable(const char *variable, const char *program_name);
int custom_setenv(const char *name, const char *value, int overwrite);
int custom_unsetenv(const char *name);
char *int_to_str(int num);
void display_custom_prompt(void);
void exit_shell(char **args);
void show_custom_environment(void);
int execute_custom_command(const char *program_name, const char *command, char *args[]);
void tokenize_input_line(char *input, char **command, char *args[], int *num_args);
void execute_command_in_custom_path(const char *program_name, const char *command, char *args[]);
int read_custom_input_line(char **input, size_t *input_length, const char *program_name);
void change_directory_custom(char *args[]);
void copy_custom_string(char *destination, const char *source);
int compare_strings(const char *str1, const char *str2);
int custom_atoi(const char *string);
size_t custom_strcspn(const char *str, const char *str2);
size_t custom_strlen(const char *str);
char *substring(const char *long_string, const char *single);
int compare_strings_n(const char *str1, const char *str2, size_t n);
char *concat_strings(char *destination, const char *source);
char *duplicate_string(const char *string);
void execute_individual_custom_command(char *program_name, char *command, char *args[]);
char *handle_custom_variables(const char *input, const char *program_name, pid_t pid);
char *find_custom_path(const char *command);
void process_custom_command(const char *command, char **args, int num_args, const char *program_name);
char *custom_strchr(const char *str, int c);
char *custom_strncpy(char *dest, const char *src, size_t n);
char *custom_strstr(const char *haystack, const char *needle);

#endif
