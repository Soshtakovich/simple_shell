#include "shell.h"

/**
 * hsh_env - Print environment variables.
 * @args: The arguments (not used in this function).
 * @envp: The environment variables.
 */
void hsh_env(char **args, char **envp)
{
int status;
ssize_t bytesRead;
ssize_t bytesWritten;
char *buffer;
FILE *pipe;
buffer = malloc(sizeof(char) * BUFSIZ);
(void)args;
(void)envp;

if (!buffer)
{
perror("Error allocating memory");
exit(EXIT_FAILURE);
}
pipe = popen("env", "r");
if (!pipe)
{
perror("Error opening pipe");
exit(EXIT_FAILURE);
}

while ((bytesRead = read(fileno(pipe), buffer, BUFSIZ)) > 0)
{
bytesWritten = write(STDOUT_FILENO, buffer, bytesRead);
if (bytesWritten != bytesRead)
{
perror("Error writing to STDOUT");
}
}
if (bytesRead < 0)
{
perror("Error reading from pipe");
}
free(buffer);
status = pclose(pipe);
if (status == -1)
{
perror("Error closing pipe");
exit(EXIT_FAILURE);
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
int exi_status;
(void)envp;

if (args[0] != NULL && _strcmp(args[0], "exit") == 0)
{
if (args[1] != NULL)
{
/* Check if the args is "exit" with arguments */
char *arg = args[1];

while (*arg != '\0')
{
if (*arg < '0' || *arg > '9')
{
/* Non-numeric character found */
fprintf(stderr, "./hsh: 1: exit: Illegal number: %s\n", args[1]);
goto exit_failure;
}
arg++;
}

exi_status = _atoi(args[1]);

if (exi_status < 0)
{
fprintf(stderr, "./hsh: 1: exit: Illegal number: %d\n", exi_status);
goto exit_failure;
}
}
else
{
exi_status = 0;
}

for (i = 0; args[i] != NULL; i++)
{
free(args[i]);
}
free(args);

/* printf("Exiting the shell with status: %d \n", exi_status); */
exit(exi_status);
}
else
{
/* Check if the args is not "exit" */
goto exit_failure;
}

exit_failure:
for (i = 0; args[i] != NULL; i++)
{
free(args[i]);
}
free(args);

/* printf("Exiting the shell with status: 2 \n"); */
exit(2);
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
