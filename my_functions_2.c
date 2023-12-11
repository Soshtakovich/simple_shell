#include "shell.h"

/**
 * _atoi - Custom string to integer conversion function.
 * @str: The input string to convert.
 *
 * Return: The converted integer.
 */
int _atoi(char *str)
{
int result = 0;
int sign = 1;

/* Handle negative sign */
if (*str == '-')
{
sign = -1;
str++;
}

/* Process each digit in the string */
while (*str >= '0' && *str <= '9')
{
result = result * 10 + (*str - '0');
str++;
}

return (sign *result);
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

