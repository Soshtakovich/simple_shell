#include "shell.h"

/**
 * get_pipe - main Function to run shell
 * Description: Get the command
 * @session: struct containing shell vars
 * Return: Entered Command.
 */
char *get_pipe()
{
char *incommand = NULL;
size_t init_size = 0;
ssize_t Command_length;

Command_length = getline(&incommand, &init_size, stdin);

if (Command_length == -1)
{
free(incommand);
exit(0);
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
 * getcommand - Get and return the entered command.
 *
 * Return: Entered Command.
 */
char *getcommand()
{
char *incommand = NULL;
size_t init_size = 0;
ssize_t Command_length;

write(STDOUT_FILENO, "$ ", 2);
Command_length = getline(&incommand, &init_size, stdin);

if (Command_length == -1)
{
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
char **Command = NULL;
char *token;
char *delimiters;
int i;
int capacity;

if (incommand == NULL || strspn(incommand, " \t\n") == _strlen(incommand))
{
/*perror("Input command is empty");*/
exit(0);
}

delimiters = " \r\n\t";
i = 0;
capacity = 5;

Command = (char **)malloc(capacity *sizeof(char *));
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
int status;

is_child = fork();

if (is_child == 0)
{

execve(fullpath, command, envp);
perror("hsh : could not execute the command");
exit(1);
}
else if (is_child > 0)
{
do
{
waitpid(is_child, &status, 0); /* WUNTRACED */
} while (!WIFEXITED(status) && !WIFSIGNALED(status));

if (WIFEXITED(status))
{
/*int exitCode;*/
/*exitCode = WEXITSTATUS(status);*/
/*printf("The exit code is : %d\n", exitCode);*/
}
else if (WIFSIGNALED(status))
{
printf("Child process terminated by signal %d\n", WTERMSIG(status));
}
}
else
{
perror("hsh");
}
}