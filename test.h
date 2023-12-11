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
/*CUSTOM FUNCTIONS 1*/

/**
* _strlen - return length of a string
* @str: The input string.
*
* Return: The length of the string
*/
size_t _strlen(char *str)
{
size_t length = 0;
while (str[length] != '\0')
{
length++;
}
return (length);
}

/**
* _strcpy - Copy a string from source to destination.
* @destination: The destination buffer.
* @source: The source string.
*
* Return: A pointer to the destination buffer.
*/
char *_strcpy(char *destination, char *source)
{
char *start = destination;
while ((*destination++ = *source++) != '\0')
{

}
return (start);
}

/**
* _strcat - Concatenate two strings.
* @destination: The destination buffer.
* @source: The source string to be appended.
*
* Return: A pointer to the destination buffer.
*/
char *_strcat(char *destination, char *source)
{
char *start = destination;
while (*destination != '\0')
{
destination++;
}
while ((*destination++ = *source++) != '\0')
{

}
return (start);
}

/**
* _strdup - Duplicate a string in dynamically allocated memory.
* @str: The input string.
*
* Return: A pointer to the duplicated string,NULL if memory allocation fails.
*/
char *_strdup(char *str)
{
size_t length;
char *duplicate;
length = strlen(str);
duplicate = malloc((length + 1) * sizeof(char));

if (duplicate == NULL)
{
/*Handle memory allocation failure*/
return (NULL);
}
_strcpy(duplicate, str);
return (duplicate);
}

/**
* _strncmp - Compare two strings up to a specified number of characters.
* @str1: The first string to compare.
* @str2: The second string to compare.
* @n: The maximum number of characters to compare.
*
* Return: An integer less than, equal to, or greater than zero if the first
* n characters of str1 are found, respectively, to be less than, to match, or
* be greater than the first n characters of str2.
*/
int _strncmp(char *str1, char *str2, size_t n)
{
while (n > 0 && *str1 && *str2)
{
if (*str1 != *str2)
{
return (*str1 - *str2);
}
str1++;
str2++;
n--;
}
return (0);
}

/*CUSTOM FUNCTIONS 1*/

/*CUSTOM FUNCTIONS 2*/

/**
 * join_str - join command to path
 * @path_token: Path Unit
 * @command: Tokenised user input
 * Return: joined path
 */
char *join_str(char *path_token, char **command)
{
char *fullPath;
size_t totalLength;

totalLength = _strlen(path_token) + 1 + _strlen(command[0]) + 1;
fullPath = (char *)malloc(totalLength);

if (fullPath == NULL)
{
perror("Could not join strings");
return (NULL);
}

_strcpy(fullPath, path_token);
_strcat(fullPath, "/");
_strcat(fullPath, command[0]);

return (fullPath);
}

/**
 * get_address - Retrieves address of a command
 * @command: The command for which the address is to be retrieved.
 * @envp: The environment variables.
 *
 * Return: A pointer to the address string.
 */
char *get_address(char **command, char **envp)
{
int i;
char *path_var = NULL;
char *path_tokens = NULL;
char *fullPath = NULL;
char *Address = NULL;

/*Find the PATH environment variable*/
for (i = 0; envp[i] != NULL; i++)
{
if (_strncmp(envp[i], "PATH=", 5) == 0)
{
path_var = _strdup(envp[i] + 5);
break;
}
}

/*Check if PATH environment variable is found*/
if (path_var == NULL)
{
fprintf(stderr, "PATH environment variable not found.\n");
exit(EXIT_FAILURE);
}

/*Tokenize the PATH variable*/
path_tokens = strtok(path_var, ":");
while (path_tokens != NULL)
{
/*Creating the full path by joining the directory and the command*/
fullPath = join_str(path_tokens, command);

if (fullPath == NULL)
{
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}

/*Check if the full path is executable*/
if (access(fullPath, X_OK) == 0)
{
/*If executable, duplicates and return the full path*/
Address = _strdup(fullPath);
if (Address == NULL)
{
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}
free(path_var);
free(fullPath);
return (Address);
}

/*If not executable, free the memory for fullPath*/
free(fullPath);
path_tokens = strtok(NULL, ":");
}

/*If no executable found, free memory and print an error message*/
free(path_var);
fprintf(stderr, "%s: Could not get its address\n", command[0]);
exit(EXIT_FAILURE);
}


/*RUN SHELL*/

/**
 * getcommand - Get and return the entered command.
 *
 * Return: Entered Command.
 */
char *getcommand()
{
char *incommand = NULL;
size_t init_size = 0;
int Command_length;

if (isatty(STDIN_FILENO))
{
write(STDOUT_FILENO, "$ ", 2);
}

Command_length = getline(&incommand, &init_size, stdin);

if (Command_length == -1) /* incommand not taken */
{
perror("Error (getline)");
free(incommand);
exit(EXIT_FAILURE);
}
else
{
if (Command_length > 0 && incommand[Command_length - 1] == '\n')
{
incommand[Command_length - 1] = '\0';
}
}

return (incommand);
}


/**
* command_tokeniser - Tokenize the entered command into tokens.
* @incommand: Entered command.
*
* Return: Tokens of entered command.
*/
char **command_tokeniser(char *incommand)
{
if (incommand == NULL)
{
perror("Input command is empty");
exit(EXIT_FAILURE);
}

char **Command = NULL;
char *token;
char *delimiters = " \r\n\t";
int i = 0;
int capacity = 5;

Command = (char **)malloc(capacity * sizeof(char *));
if (!Command)
{
perror("Memory allocation error");
exit(EXIT_FAILURE);
}

token = strtok(incommand, delimiters);

while (token != NULL)
{
Command[i] = _strdup(token);  /*Duplicate the token to store in the array*/
i++;

if (i >= capacity)
{
capacity *= 2;
Command = (char **)realloc(Command, capacity *sizeof(char *));
if (!Command)
{
perror("Memory reallocation error");
exit(EXIT_FAILURE);
}
}
token = strtok(NULL, delimiters);
}

Command[i] = NULL;/*Null-terminate the array*/

return (Command);
}


/**
 * exe - Main executing function.
 * @command: Entered command.
 * @envp: Environment variables.
 * @fullpath: Address of the executable file.
 */
void exe(char **envp, char **command, char *fullpath)
{
pid_t is_child;
int exitCode;

is_child = fork();

if (is_child == 0)
{
/*In the child process*/
execve(fullpath, command, envp);

/*If execve fails*/
perror("hsh: Could not execute the command");
free(command);
free(fullpath);
exit(EXIT_FAILURE);
}
else if (is_child > 0)
{
/*In the parent process*/
int status;
waitpid(is_child, &status, 0);

if (WIFEXITED(status))
{
exitCode = WEXITSTATUS(status);
/*Do something with the exitCode if needed*/
}
else if (WIFSIGNALED(status))
{
fprintf(stderr, "Child process terminated by signal %d\n", WTERMSIG(status));
}
}
else
{
perror("Fork failed");
exit(EXIT_FAILURE);
}
}


/*BUILTINS*/

/**
 * struct builtin - represents a built-in command
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


/**
 * hsh_env - Print environment variables.
 * @args: The arguments (not used in this function).
 * @envp: The environment variables.
 */
void hsh_env(char **args, char **envp)
{
int i;
(void)args;

for (i = 0; envp[i] != NULL; i++)
{
printf("%s\n", envp[i]);
}
}

/**
* hsh_exit - Exit the shell.
* @args: The arguments (not used in this function).
* @envp: The environment variables (not used in this function).
*/
void hsh_exit(char **args, char **envp)
{
(void)envp;
(void)args;
exit(0);
}

/**
* hsh_cd - Change the working directory.
* @args: The arguments.
* @envp: The environment variables (not used in this function).
*/
void hsh_cd(char **args, char **envp)
{
if (args[1] == NULL)
{
fprintf(stderr, "./hsh: cd: missing argument\n");
}
else
{
if (chdir(args[1]) != 0)
{
perror("./hsh: cd: ");
}
}
(void)envp;
}

/**
* hsh_help - Print the shell's help text.
* @args: The arguments (not used in this function).
* @envp: The environment variables (not used in this function).
*/
void hsh_help(char **args, char **envp)
{
char *helptext;
(void)args;
(void)envp;

helptext =
"SIMPLE SHELL : ALX SIMPLE SHELL PROJECT\n"
"The following commands are built in:\n"
"  cd       Change the working directory.\n"
"  exit     Exit the shell.\n"
"  env      Print environment variables.\n"
"  help     Print this help text.\n";

printf("%s", helptext);
}



/**
 * builtins - Array of structures representing built-in commands
 *
 * Description: This array associates the names of built-in commands with their
 * corresponding functions. Each element of the array is a struct builtin
 * containing the name of the command and a function pointer to the associated
 * implementation.
 */
struct builtin builtins[] = {
{"help", hsh_help},  /*Command to display help information*/
{"exit", hsh_exit},  /*Command to exit the shell*/
{"cd", hsh_cd},      /*Command to change the current directory*/
{"env", hsh_env},    /*Command to display environment variables*/
};

/**
* hsh_num_builtins - Returns the number of registered commands.
*
* Return: The number of registered commands.
*/
int hsh_num_builtins(void)
{
return (sizeof(builtins) / sizeof(struct builtin));
}

/*PROTOTYPES*/


/*EXECUTES*/

/**
 * executez - Initiates execution.
 * @envp: Environment Variables.
 * @command: Tokenized user input.
 * Return: None.
 */
void executez(char **command, char **envp)
{
int i;

/*Execute built-in commands*/
for (i = 0; i < hsh_num_builtins(); i++)
{
if (strcmp(command[0], builtins[i].name) == 0)
{
builtins[i].func(command, envp);
return;
}
}

/*Execute external commands*/
if (access(command[0], X_OK) == 0)
{
exe(envp, command, command[0]);
}
else
{
char *Command_ext = get_address(command, envp);

if (Command_ext != NULL && access(Command_ext, X_OK) == 0)
{
exe(envp, command, Command_ext);
free(Command_ext);
}
else
{
fprintf(stderr, "hsh: %s: command not found\n", command[0]);
}
}
}


#endif
