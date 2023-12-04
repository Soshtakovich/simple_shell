#include "shell.h"

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
int i;
(void)envp;


/*Free the allocated memory for each token in the Command array*/
for (i = 0; args[i] != NULL; i++)
{
free(args[i]);
}

/*Free the allocated memory for the command array*/
free(args);

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
