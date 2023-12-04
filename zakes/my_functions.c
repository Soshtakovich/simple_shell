#include "shell.h"

/*CUSTOM FUNCTIONS 1*/

/**
* _strlen - return length of a string
* @str: The input string
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
 * _strcmp - Compare two strings.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 *
 * Return: An integer less than, equal to, or greater than zero if str1
 * is found, respectively, to be less than, to match, or be greater than str2.
 */
int _strcmp(char *str1, char *str2)
{
while (*str1 && *str2 && (*str1 == *str2))
{
str1++;
str2++;
}

return (*str1 - *str2);
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
/*fprintf(stderr, "PATH environment variable not found.\n");*/
fprintf(stderr, "./hsh: 1: %s: not found\n", command[0]);
exit(127);
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
/*fprintf(stderr, "%s: Could not get its address\n", command[0]);*/
fprintf(stderr, "./hsh: 1: %s: not found\n", command[0]);
exit(127);
}
