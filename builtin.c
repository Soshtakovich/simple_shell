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
char *new_dir;
char cwd[1024];

/* If no argument is given, use $HOME */
if (args[1] == NULL)
{
new_dir = getenv("HOME");
}
else if (_strcmp(args[1], "-") == 0)
{
/* If the argument is "-", change to the previous directory */
new_dir = getenv("OLDPWD");
if (new_dir == NULL)
{
fprintf(stderr, "hsh: cd: OLDPWD not set\n");
return;
}
fprintf(stdout, "%s\n", new_dir);
}
else
{
new_dir = args[1];
}

/* Change the directory */
if (chdir(new_dir) != 0)
{
/* If chdir fails, print an error message */
fprintf(stderr, "hsh: cd: %s: No such file or directory\n", new_dir);
return;
}

/* Update the PWD environment variable */
if (getcwd(cwd, sizeof(cwd)) != NULL)
{
update_pwd(envp, cwd);
}
else
{
/* If getcwd fails, print an error message */
fprintf(stderr, "hsh: cd: error updating PWD\n");
}
}


/**
* update_pwd - Update the PWD environment variable with the new directory .
* @new_pwd: Nerw working Directory
* @envp: The environment variables (not used in this function).
*/
void update_pwd(char **envp, char *new_pwd)
{
/* Find the position of the PWD environment variable in envp */
int index;
int i;

index = -1;

for (i = 0; envp[i] != NULL; i++)
{
if (_strncmp(envp[i], "PWD=", 4) == 0)
{
index = i;
break;
}
}

/* If PWD is found, update its value using putenv */
if (index != -1)
{
char env_var[1024];
snprintf(env_var, sizeof(env_var), "PWD=%s", new_pwd);
if (putenv(env_var) != 0)
{
perror("putenv");
exit(EXIT_FAILURE);
}
}
}
