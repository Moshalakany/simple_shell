#include "simple_shell.h"
/**
 * search_for_path - finds the PATH variable
 * @Env: array of environment main_var
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *search_for_path(char **Env)
{
	unsigned int count1, count2;
	char *Path = "PATH=";

	for (count1 = 0; Env[count1] != NULL; count1++)
	{
		for (count2 = 0; count2 < 5; count2++)
			if (Path[count2] != Env[count1][count2])
				break;
		if (count2 == 5)
			break;
	}
	return (Env[count1]);
}
/**
 * check_directory - checks if the cmd is a part of a Path
 * @str: cmd
 *
 * Return: 1 on success, 0 on failure
 */
int check_directory(char *str)
{
	unsigned int counter;

	for (counter = 0; str[counter]; counter++)
	{
		if (str[counter] == '/')
			return (1);
	}
	return (0);
}
/**
 * path_exec - executes a cmd in the Path
 * @cmd: full Path to the cmd
 * @var: pointer to struct of main_var
 *
 * Return: 0 on success, 1 on failure
 */
int path_exec(char *cmd, m_var *var)
{
	pid_t sub_Pid;

	if (access(cmd, X_OK) == 0)
	{
		sub_Pid = fork();
		if (sub_Pid == -1)
			view_error(var, NULL);
		if (sub_Pid == 0)
		{
			if (execve(cmd, var->av, var->env) == -1)
				view_error(var, NULL);
		}
		else
		{
			wait(&var->status);
			if (WIFEXITED(var->status))
				var->status = WEXITSTATUS(var->status);
			else if (WIFSIGNALED(var->status) && WTERMSIG(var->status) == SIGINT)
				var->status = 130;
			return (0);
		}
		var->status = 127;
		return (1);
	}
	else
	{
		view_error(var, ": Permission denied\n");
		var->status = 126;
	}
	return (0);
}

/**
 * check_path - checks if the cmd is in the PATH
 * @var: main_var
 *
 * Return: void
 */
void check_path(m_var *var)
{
	char *path, *path_duplicated = NULL, *check = NULL;
	struct stat Buf;
	char **tokens_Path;
	unsigned int count = 0, exe = 0;

	if (check_directory(var->av[0]))
		exe = cwd_exec(var);
	else
	{
		path = search_for_path(var->env);
		if (path != NULL)
		{
			path_duplicated = _strdup(path + 5);
			tokens_Path = tokenize(path_duplicated, ":");
			for (count = 0; tokens_Path && tokens_Path[count]; count++, free(check))
			{
				check = _strcat(tokens_Path[count], var->av[0]);
				if (stat(check, &Buf) == 0)
				{
					exe = path_exec(check, var);
					free(check);
					break;
				}
			}
			free(path_duplicated);
			if (tokens_Path == NULL)
			{
				var->status = 127;
				exit_prog(var);
			}
		}
		if (path == NULL || tokens_Path[count] == NULL)
		{
			view_error(var, ": not found\n");
			var->status = 127;
		}
		free(tokens_Path);
	}
	if (exe == 1)
		exit_prog(var);
}
/**
 * cwd_exec - executes the cmd in the current working directory
 * @var: pointer to struct of main_var
 *
 * Return: 0 on success, 1 on failure
 */
int cwd_exec(m_var *var)
{
	struct stat Buff;
	pid_t sub_Pid;

	if (stat(var->av[0], &Buff) == 0)
	{
		if (access(var->av[0], X_OK) == 0)
		{
			sub_Pid = fork();
			if (sub_Pid == -1)
				view_error(var, NULL);
			if (sub_Pid == 0)
			{
				if (execve(var->av[0], var->av, var->env) == -1)
					view_error(var, NULL);
			}
			else
			{
				wait(&var->status);
				if (WIFEXITED(var->status))
					var->status = WEXITSTATUS(var->status);
				else if (WIFSIGNALED(var->status) && WTERMSIG(var->status) == SIGINT)
					var->status = 130;
				return (0);
			}
			var->status = 127;
			return (1);
		}
		else
		{
			view_error(var, ": Permission denied\n");
			var->status = 126;
		}
		return (0);
	}
	view_error(var, ": not found\n");
	var->status = 127;
	return (0);
}

