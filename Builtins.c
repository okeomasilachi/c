#include "main.h"

/**
 * cd_command - changes directory to the specified path
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @argc: argument count
 *
 * Return: void
*/
void cd_command(char **args, char *NAME, int argc)
{
	char *ok, *old, *new;
	int i;

	(void)argc, (void)NAME, (void)new;

	if (!args[1])
	{
		ok = _getenv("HOME");
		chdir(ok);
		return;
	}
	if ((i = _strcmp(args[1], "-")) == 0)
	{
		old = _getenv("OLDPWD");
		chdir(old);
		new = _getenv("PWD");
		pf(STDOUT_FILENO, "%s\n", new);
	}
	else
	{
		ok = _getenv("PWD");
		if (chdir(args[1]) == 0)
		{
			ok = _getenv("PWD");
			pf(STDOUT_FILENO, "%s\n", ok);
		}
		else
			pf(STDERR_FILENO, "%s: %d: %s: can't cd to %s\n", NAME, argc, args[0], args[1]);
	}
}

/**
 * exit_command - exits the program
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @argc: argument count
 *
 * Return: void
*/
void exit_command(char **args, char *NAME, int argc)
{
	(void)NAME, (void)argc;

	if (args[1] == NULL)
		exit(EXIT_SUCCESS);
	else if (args[1] != NULL)
	{
		exit(_atoi(args[1]));
	}
}

/**
 * setenv_command - sets the specified environ
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @argc: argument count
 *
 * Return: void
*/
void setenv_command(char **args, char *NAME, int argc)
{
	(void)NAME, (void)argc;

	if (args[1] == NULL || args[2] == NULL)
		pf(STDERR_FILENO, "Usage: setenv NAME value\n");
	else
	{
		if (_setenv(args[1], args[2], 1) != 0)
			perror("setenv");
	}
}

/**
 * _command - changes directory to the specified path
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @argc: argument count
 *
 * Return: void
*/
void unsetenv_command(char **args,  char *NAME, int argc)
{
	(void)NAME, (void)argc;

	if (args[1] == NULL)
		pf(STDERR_FILENO, "unsetenv: missing argument\n");
	else
	{
		if (_unsetenv(args[1]) != 0)
			perror("unsetenv");
	}
}

/**
 * _command - changes directory to the specified path
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @argc: argument count
 *
 * Return: void
*/
void help_command(char **args,  char *NAME, int argc)
{
	(void)NAME, (void)argc;

	if (args[1] == NULL)
	{
		pf(STDOUT_FILENO, "	   	This is a simple shell program\n");
		pf(STDOUT_FILENO, "Authors: Ebiri ThankGod, Onyedibia Okeomasilachi.\n");
	}
}
