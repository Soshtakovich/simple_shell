#include "shell.h"
/**
 * main - main block
 * Description: Get the process id of the current program
 * Return: 0
 */

int betty(void)
{
int my_pid;

my_pid = getpid();
printf("My current processing id is %d\n", my_pid);

return (0);
}

