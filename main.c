#include "shell.h"



/**
 * main - Initation funtion
 * @argc: number of the arguments
 * @argv: arguments
 * @envp: enviroments
 * Return: success full 1 or fail -1
 **/

int main(int argc, char **argv, char **envp)
{
char *incommand;
char **Command;
int i;
(void)argc;
(void)argv;

while (1)
{
/*Get user input*/

if (isatty(fileno(stdin)))
{
incommand = getcommand(); /*TERMINAL*/
}
else
{
incommand = get_pipe(); /*PIPED*/
}


/*Tokenize the entered command and return array of arrays*/
Command = command_tokeniser(incommand);

/*Free the allocated memory for incommand, in case of exit*/
free(incommand);

/*Execute the entered command*/
executez(Command, envp);


/*free(incommand);*/

/*Free the allocated memory for each token in the command array*/
for (i = 0; Command[i] != NULL; i++)
{
free(Command[i]);
}

/*Free the allocated memory for the command array*/
free(Command);
}

return (0); /*Return 0 to indicate successful execution*/
}

