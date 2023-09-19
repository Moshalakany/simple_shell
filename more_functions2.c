#include "simple_shell.h"
/**
 * search_for_key - finds an environment variable
 * @env: array of environment main_var
 * @key: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **search_for_key(char **env, char *key)
{
	unsigned int count1, count2, length;

	length = _strlen(key);
	for (count1 = 0; env[count1] != NULL; count1++)
	{
		for (count2 = 0; count2 < length; count2++)
			if (key[count2] != env[count1][count2])
				break;
		if (count2 == length && env[count1][count2] == '=')
			return (&env[count1]);
	}
	return (NULL);
}

/**
 * add_new_key - create a new environment variable
 * @var: pointer to struct of main_var
 *
 */
void add_new_key(m_var *var)
{
	char **tmpEnv;
	unsigned int counter;

	for (counter = 0; var->env[counter] != NULL; counter++)
		;
	tmpEnv = malloc(sizeof(char *) * (counter + 2));
	if (tmpEnv == NULL)
	{
		view_error(var, NULL);
		var->status = 127;
		exit_prog(var);
	}
	for (counter = 0; var->env[counter] != NULL; counter++)
		tmpEnv[counter] = var->env[counter];
	tmpEnv[counter] = add_new_value(var->av[1], var->av[2]);
	if (tmpEnv[counter] == NULL)
	{
		view_error(var, NULL);
		free(var->buffer);
		free(var->commands);
		free(var->av);
		free_Env(var->env);
		free(tmpEnv);
		exit(127);
	}
	tmpEnv[counter + 1] = NULL;
	free(var->env);
	var->env = tmpEnv;
}


/**
 * add_new_value - create a new environment variable string
 * @key: variable name
 * @value: variable value
 *
 * Return: pointer to the new string;
 */
char *add_new_value(char *key, char *value)
{
	char *tmp;
	unsigned int length1, length2, count1, count2;

	length1 = _strlen(key);
	length2 = _strlen(value);
	tmp = malloc(sizeof(char) * (length1 + length2 + 2));
	if (tmp == NULL)
		return (NULL);
	for (count1 = 0; key[count1] != '\0'; count1++)
		tmp[count1] = key[count1];
	tmp[count1] = '=';
	for (count2 = 0; value[count2] != '\0'; count2++)
		tmp[count1 + 1 + count2] = value[count2];
	tmp[count1 + 1 + count2] = '\0';
	return (tmp);
}

/**
 * _uitoa - converts an unsigned into a string
 * @count: unsigned int to convert
 *
 * Return: pointer to the converted string
 */

char *_uitoa(unsigned int count)
{
	char *num_str;
	unsigned int temp, digit;

	temp = count;
	for (digit = 0; temp != 0; digit++)
		temp /= 10;
	num_str = malloc(sizeof(char) * (digit + 1));
	if (num_str == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	num_str[digit] = '\0';
	for (--digit; count; --digit)
	{
		num_str[digit] = (count % 10) + '0';
		count /= 10;
	}
	return (num_str);
}


/**
 * _atoi - converts a string into an integer
 * @s: string to convert
 * Return: the integer value, or -1 if an error occurs
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int total = 0;
	char null_flag = 0;

	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == '-')
			sign *= -1;
		if (*s >= '0' && *s <= '9')
		{
			null_flag = 1;
			total = total * 10 + (*s - '0');
		}
		else if (*s < '0' || *s > '9')
		{
			if (null_flag == 1)
				break;
		}
		s++;
	}
	if (sign < 0)
		total = (-1 * (total));
	return (total);
}
