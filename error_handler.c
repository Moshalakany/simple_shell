#include "simple_shell.h"
/**
 * E_puts - prints a string to standard error
 * @str: string to print
 *
 * Return: void
 */
void E_puts(char *str)
{
	ssize_t size, length;

	size = _strlen(str);
	length = write(STDERR_FILENO, str, size);
	if (length != size)
	{
		perror("Fatal Error");
		exit(1);
	}

}
/**
 * view_error - prints error messages to standard error
 * @var: pointer to struct of main_var
 * @msg: message to print out
 *
 * Return: void
 */
void view_error(m_var *var, char *msg)
{
	char *ch;

	E_puts(var->argv[0]);
	E_puts(": ");
	ch = _uitoa(var->count);
	E_puts(ch);
	free(ch);
	E_puts(": ");
	E_puts(var->av[0]);
	if (msg)
	{
		E_puts(msg);
	}
	else
		perror("");
}

