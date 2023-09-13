#include "simple_shell.h"

/**
 * exit_prog - exit program
 * @var: main_var
 *
 * Return: void
 */
void exit_prog(m_var *var)
{
	int status;

	if (_strcmpr(var->av[0], "exit") == 0 && var->av[1] != NULL)
	{
		status = _atoi(var->av[1]);
		if (status == -1)
		{
			var->status = 2;
			view_error(var, ": Illegal number: ");
			E_puts(var->av[1]);
			E_puts("\n");
			free(var->commands);
			var->commands = NULL;
			return;
		}
		var->status = status;
	}
	free(var->buffer);
	free(var->av);
	free(var->commands);
	free_Env(var->env);
	exit(var->status);
}
/**
 * check_builtins - checks if the command is a builtin
 * @var: main_var
 *
 * Return: pointer to the function or NULL
 */
void (*check_builtins(m_var *var))(m_var *var)
{
	builtins_t validate[] = {
		{"exit", exit_prog},
		{"env", P_Env},
		{"setenv", _setEnv},
		{"unsetenv", _unsetEnv},
		{NULL, NULL}
	};
	unsigned int counter;

	for (counter = 0; validate[counter].func != NULL; counter++)
	{
		if (_strcmpr(var->av[0], validate[counter].name) == 0)
			break;
	}
	if (validate[counter].func != NULL)
		validate[counter].func(var);
	return (validate[counter].func);
}


/**
 * P_Env - prints the current environment
 * @vars: struct of main_var
 *
 * Return: void.
 */
void P_Env(m_var *vars)
{
	unsigned int counter;

	for (counter = 0; vars->env[counter]; counter++)
	{
		_puts(vars->env[counter]);
		_puts("\n");
	}
	vars->status = 0;
}

/**
 * _unsetEnv - remove an environment variable
 * @vars: pointer to a struct of main_var
 *
 * Return: void
 */
void _unsetEnv(m_var *vars)
{
	char **keyWord, **tmpEnv;

	unsigned int count1, count2;

	if (vars->av[1] == NULL)
	{
		view_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	keyWord = search_for_key(vars->env, vars->av[1]);
	if (keyWord == NULL)
	{
		view_error(vars, ": No variable to unset");
		return;
	}
	for (count1 = 0; vars->env[count1] != NULL; count1++)
		;
	tmpEnv = malloc(sizeof(char *) * count1);
	if (tmpEnv == NULL)
	{
		view_error(vars, NULL);
		vars->status = 127;
		exit_prog(vars);
	}
	for (count1 = 0; vars->env[count1] != *keyWord; count1++)
		tmpEnv[count1] = vars->env[count1];
	for (count2 = count1 + 1; vars->env[count2] != NULL; count2++, count1++)
		tmpEnv[count1] = vars->env[count2];
	tmpEnv[count1] = NULL;
	free(*keyWord);
	free(vars->env);
	vars->env = tmpEnv;
	vars->status = 0;
}
/**
 * _setEnv - create a new environment variable, or edit an existing variable
 * @var: pointer to struct of main_var
 *
 * Return: void
 */
void _setEnv(m_var *var)
{
	char **keyword;
	char *vars;

	if (var->av[1] == NULL || var->av[2] == NULL)
	{
		view_error(var, ": Incorrect number of arguments\n");
		var->status = 2;
		return;
	}
	keyword = search_for_key(var->env, var->av[1]);
	if (keyword == NULL)
		add_new_key(var);
	else
	{
		vars = add_new_value(var->av[1], var->av[2]);
		if (vars == NULL)
		{
			view_error(var, NULL);
			free(var->buffer);
			free(var->commands);
			free(var->av);
			free_Env(var->env);
			exit(127);
		}
		free(*keyword);
		*keyword = vars;
	}
	var->status = 0;
}
