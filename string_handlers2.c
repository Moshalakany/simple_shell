#include "simple_shell.h"

/**
 * check_contain - checks if a character matches any in a string
 * @ch: character to check
 * @str: string to check
 *
 * Return: 1 if match, 0 if not
 */

unsigned int check_contain(char ch, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (ch == str[i])
			return (1);
	}
	return (0);
}

/**
 * _Strtok - custom strtok
 * @str: string to tokenize
 * @delimiter: delimiter to tokenize against
 * Return: pointer to the next token or NULL
 */
char *_Strtok(char *str, const char *delimiter)
{
	unsigned int count;
	static char *start_token;
	static char *Next;

	if (str != NULL)
		Next = str;
	start_token = Next;
	if (start_token == NULL)
		return (NULL);
	for (count = 0; Next[count] != '\0'; count++)
	{
		if (check_contain(Next[count], delimiter) == 0)
			break;
	}
	if (Next[count] == '\0' || Next[count] == '#')
	{
		Next = NULL;
		return (NULL);
	}
	start_token = Next + count;
	Next = start_token;
	for (count = 0; Next[count] != '\0'; count++)
	{
		if (check_contain(Next[count], delimiter) == 1)
			break;
	}
	if (Next[count] == '\0')
		Next = NULL;
	else
	{
		Next[count] = '\0';
		Next = Next + count + 1;
		if (*Next == '\0')
			Next = NULL;
	}
	return (start_token);
}

