#include "simple_shell.h"

/**
 * _realloc - reallocates a pointer to double the space
 * @ptr: pointer to the old array
 * @size: pointer to number of elements in the old array
 *
 * Return: pointer to the new array
 */

char **_realloc(char **ptr, size_t *size)
{
	size_t i;
	char **tmp;

	tmp = malloc(sizeof(char *) * ((*size) + 10));
	if (tmp == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		tmp[i] = ptr[i];
	}
	*size += 10;
	free(ptr);
	return (tmp);
}
