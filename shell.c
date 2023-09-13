#include "simple_shell.h"


/**
 * signal_handler - handles ^C signal interupt
 * @uuv: unused variable (required for signal function prototype)
 */
static void signal_handler(int uuv)
{
	(void) uuv;
	if (signal_flag == 0)
		_puts("\n$ ");
	else
		_puts("\n");
}
/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment main_var
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	unsigned int check_pipe = 0, counter;
	size_t buffer_length = 0;
	m_var vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.argv = argv;
	vars.env = create_env(environment);
	signal(SIGINT, signal_handler);
	if (!isatty(STDIN_FILENO))
		check_pipe = 1;
	if (check_pipe == 0)
		_puts("$ ");
	signal_flag = 0;
	while (getline(&(vars.buffer), &buffer_length, stdin) != -1)
	{
		signal_flag = 1;
		vars.count++;
		vars.commands = tokenize(vars.buffer, ";");
		for (counter = 0; vars.commands && vars.commands[counter] != NULL; counter++)
		{
			vars.av = tokenize(vars.commands[counter], "\n \t\r");
			if (vars.av && vars.av[0])
				if (check_builtins(&vars) == NULL)
					check_path(&vars);
			free(vars.av);
		}
		free(vars.buffer);
		free(vars.commands);
		signal_flag = 0;
		if (check_pipe == 0)
			_puts("$ ");
		vars.buffer = NULL;
	}
	if (check_pipe == 0)
		_puts("\n");
	free_Env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}

