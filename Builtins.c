#include "main.h"

/**
 * cd_command - changes directory to the specified path
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void cd_command(char **args, char *NAME, int num)
{
	char *ok, *old, *new;

	(void)new;

	if (!args[1])
	{
		ok = _getenv("HOME");
		chdir(ok);
		return;
	}
	if (_strcmp(args[1], "-") == 0)
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
			pf(2, "%s: %d: %s: can't cd to %s\n", NAME, num, args[0], args[1]);
	}
}

/**
 * exit_command - exits the program
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/

void exit_command(char **args, char *NAME, int num)
{
	int i;
	int isNumber = 1;

	if (args[1] == NULL)
		exit(EXIT_SUCCESS);
	else if (args[1] != NULL)
	{
		for (i = 0; args[1][i] != '\0'; i++)
		{
			if (!_isdigit(args[1][i]))
			{
				isNumber = 0;
				break;
			}
		}
		if (!isNumber)
			pf(2, "%s: %d: %s: Illegal number: %s\n", NAME, num, args[0], args[1]);
		else
			exit(_atoi(args[1]));
	}
}

/**
 * setenv_command - sets the specified environ
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void setenv_command(char **args, char *NAME, int num)
{
	(void)NAME, (void)num;

	if (args[1] == NULL || args[2] == NULL)
		pf(2, "%s: %d: %s: Usage: setenv NAME value\n", NAME, num, args[0]);
	else
	{
		if (_setenv(args[1], args[2], 1) != 0)
			perror("setenv");
	}
}

/**
 * unsetenv_command - unsets an environmental variable
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void unsetenv_command(char **args,  char *NAME, int num)
{
	(void)NAME, (void)num;

	if (args[1] == NULL)
		pf(STDERR_FILENO, "%s: %d: %s: missing argument\n", NAME, args[0], args[1]);
	else
	{
		if (!_getenv(args[1]))
			pf(STDERR_FILENO, "%s: %d: %s: %s not set\n", NAME, num, args[0], args[1]);
		if (_unsetenv(args[1]) != 0)
			perror("unsetenv");
	}
}

/**
 * help_command - print help
 * @args: arguments to work with
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: void
*/
void help_command(char **args,  char *NAME, int num)
{
	(void)NAME, (void)num;

	if (args[1] == NULL)
	{
		pf(STDOUT_FILENO, "	This is a simple shell program\n");
		pf(STDOUT_FILENO, "\nAuthors: Ebiri ThankGod, Onyedibia Okeomasilachi.\n");
	}
}
