#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
/**
 * struct main_var - main_var
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment main_var
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 * @status: exit status
 * @commands: double pointer to commands
 */
typedef struct main_var
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
} m_var;

/**
 * struct bltn_func - struct for the builtin functions
 * @name: name of builtin command
 * @func: function for corresponding builtin
 */
typedef struct bltn_func
{
	char *name;
	void (*func)(m_var *);
} builtins_t;

/* variable for ^C handling */
unsigned int signal_flag;

unsigned int _strlen(char *str);
ssize_t _puts(char *str);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
char *_strdup(char *strtodup);

void free_Env(char **env);
char **create_env(char **env);

void (*check_builtins(m_var *vars))(m_var *vars);
void exit_prog(m_var *vars);
void P_Env(m_var *vars);
void _setEnv(m_var *vars);
void _unsetEnv(m_var *vars);

void check_path(m_var *vars);
int path_exec(char *command, m_var *vars);
char *search_for_path(char **env);
int cwd_exec(m_var *vars);
int check_directory(char *str);

void E_puts(char *str);
void view_error(m_var *vars, char *msg);
char *_uitoa(unsigned int count);

char **search_for_key(char **env, char *key);
int _atoi(char *str);
char *add_new_value(char *key, char *value);
void add_new_key(m_var *vars);

char **_realloc(char **ptr, size_t *size);
char **tokenize(char *buffer, char *delimiter);
char *_Strtok(char *str, const char *delim);
unsigned int check_contain(char c, const char *str);

#endif
