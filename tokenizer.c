#include "simple_shell.h"


/**
 * tokenize - tokenizes a buff with a delim
 * @buff: buff to tokenize
 * @delim: delim to tokenize along
 *
 * Return: pointer to an array of pointers to the toks
 */
char **tokenize(char *buff, char *delim)
{
	size_t counter = 0, Max = 10;
	char **toks = NULL;

	if (buff == NULL)
		return (NULL);
	toks = malloc(sizeof(char *) * Max);
	if (toks == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((toks[counter] = _Strtok(buff, delim)) != NULL)
	{
		counter++;
		if (counter == Max)
		{
			toks = _realloc(toks, &Max);
			if (toks == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		buff = NULL;
	}
	return (toks);
}

