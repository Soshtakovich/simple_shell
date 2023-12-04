#ifndef SHELL_H
#define SHELL_H
/**
 * shell.h - Contains prototypes for simple shell
 * Author : Zakes Matsimbe and Andy Vuma
 */

/*OTHER HEADER FILES*/
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <glob.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <stddef.h>


/*PROTOTYPES*/

/*CUSTOM FUNCTIONS*/

int betty(void);
size_t _strlen(char *str);
char *_strcpy(char *destination, char *source);
char *_strcat(char *destination, char *source);
char *_strdup(char *str);
int _strcmp(char *str1, char *str2);
int _strncmp(char *str1, char *str2, size_t n);
char *join_str(char *path_token, char **command);
char *get_address(char **command, char **envp);

/*RUN SHELL*/

char *get_pipe();
char *getcommand();
char **command_tokeniser(char *incommand);
int hsh_num_builtins(void);
void executez(char **command, char **envp);
void exe(char **envp, char **command, char *fullpath);

/*BUILTINS*/

void hsh_env(char **args, char **envp);
void hsh_exit(char **args, char **envp);
void hsh_cd(char **args, char **envp);
void hsh_help(char **args, char **envp);
void (*func)(char **args, char **envp);

/*BUILTINS*/

/**
 * struct builtin - represents a built-in Command
 * Description: This structure is used to associate the name of a builtin
 * command with its corresponding function.
 * @name: The name of the builtin command
 * @func: A function pointer to the corresponding built-in function
 */
struct builtin
{
char *name;
void (*func)(char **args, char **envp);
};


#endif
