#include "shell.h"

/**
 * builtins - Array of structures representing built-in Commands
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
if (_strcmp(command[0], builtins[i].name) == 0)
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
