#include "simple_shell.h"
/**
 * _strlen - returns the length of a string
 * @str: string to be measured
 * Return: length of string
 */
unsigned int _strlen(char *str)
{
	unsigned int length;

	length = 0;

	for (length = 0; str[length]; length++)
		;
	return (length);
}


/**
 * _strdup - returns pointer to new mem alloc space which contains duplicate
 * @strtodup: string to be duplicated
 *
 * Return: a pointer to the new duplicated string
 */
char *_strdup(char *strtodup)
{
	int length, counter;
	char *duplicate;

	if (strtodup == 0)
		return (NULL);

	for (length = 0; strtodup[length]; length++)
		;
	duplicate = malloc((length + 1) * sizeof(char));

	for (counter = 0; counter <= length; counter++)
		duplicate[counter] = strtodup[counter];

	return (duplicate);
}

/**
 * _strcmpr - compares two strings
 * @strcmp1: first string, of two, to be compared in length
 * @strcmp2: second string, of two, to be compared
 * Return: 0 on success, anything else is a failure
 */
int _strcmpr(char *strcmp1, char *strcmp2)
{
	int counter;

	counter = 0;
	while (strcmp1[counter] == strcmp2[counter])
	{
		if (strcmp1[counter] == '\0')
			return (0);
		counter++;
	}
	return (strcmp1[counter] - strcmp2[counter]);
}
/**
 * _puts - writes a string to standard output
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t _puts(char *str)
{
	ssize_t length, size;

	length = _strlen(str);
	size = write(STDOUT_FILENO, str, length);
	if (size != length)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (size);
}

/**
 * _strcat - concatenates two strings
 * @strc1: first string
 * @strc2: second string
 * Return: pointer
 */

char *_strcat(char *strc1, char *strc2)
{
	unsigned int length1 = 0, length2 = 0, newlength, count1, count2;
	char *concStr;

	if (strc1 == NULL)
		length1 = 0;
	else
	{
		for (length1 = 0; strc1[length1]; length1++)
			;
	}
	if (strc2 == NULL)
		length2 = 0;
	else
	{
		for (length2 = 0; strc2[length2]; length2++)
			;
	}
	newlength = length1 + length2 + 2;
	concStr = malloc(newlength * sizeof(char));
	if (concStr == NULL)
		return (NULL);
	for (count1 = 0; count1 < length1; count1++)
		concStr[count1] = strc1[count1];
	concStr[count1] = '/';
	for (count2 = 0; count2 < length2; count2++)
		concStr[count1 + 1 + count2] = strc2[count2];
	concStr[length1 + length2 + 1] = '\0';
	return (concStr);
}


