#include "simple_shell.h"
/**
 * free_Env - free the shell's environment
 * @env: shell's environment
 *
 */

void free_Env(char **env)
{
	unsigned int counter;

	for (counter = 0; env[counter] != NULL; counter++)
		free(env[counter]);
	free(env);
}

/**
 * create_env -  pass shell environment to main
 * @env: environment passed to main
 *
 * Return: pointer to the new environment
 */

char **create_env(char **env)
{
	size_t i;
	char **tmpEnv = NULL;

	for (i = 0; env[i] != NULL; i++)
		;
	tmpEnv = malloc(sizeof(char *) * (i + 1));
	if (tmpEnv == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (i = 0; env[i] != NULL; i++)
		tmpEnv[i] = _strdup(env[i]);
	tmpEnv[i] = NULL;
	return (tmpEnv);
}
