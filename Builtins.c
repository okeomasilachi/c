#include "main.h"

/**
 *
*/
void cd_command(char **args, char *NAME, int argc)
{
	char *ok, *old, *new;
	int i;

	(void)argc, (void)NAME;

	if (!args[1])
	{
		ok = getenv("HOME");
		chdir(ok);
		puts(ok);
		return;
	}
	if ((i = strcmp(args[1], "-")) == 0)
	{
		old = getenv("OLDPWD");
		new = getenv("PWD");
		setenv("OLDPWD", new, 1);
		setenv("PWD", old, 1);
		chdir(old);
		puts(old);
	}
	else
	{
		ok = getenv("PWD");
		if (chdir(args[1]) == 0)
		{
			setenv("OLDPWD", ok, 1);
			ok = getenv("PWD");
			puts(ok);
			setenv("PWD", ok, 1);
		}
		else
			dprintf(STDERR_FILENO, "%s: %d: %s: can't cd to %s\n", NAME, argc, args[0], args[1]);
	}
}

/**
 * 
*/
void exit_command(char **args, char *NAME, int argc)
{
	(void)NAME, (void)argc;

	if (args[1] == NULL)
		exit(EXIT_SUCCESS);
	else if (args[1] != NULL)
	{
		exit(atoi(args[1]));
	}
}

/**
 * 
*/
void setenv_command(char **args, char *NAME, int argc)
{
	(void)NAME, (void)argc;

	if (args[1] == NULL || args[2] == NULL)
		dprintf(STDERR_FILENO, "setenv: missing argument\n");
	else
	{
		if (setenv(args[1], args[2], 1) != 0)
			perror("setenv");
	}
}

/**
 * 
*/
void unsetenv_command(char **args,  char *NAME, int argc)
{
	(void)NAME, (void)argc;

	if (args[1] == NULL)
		dprintf(STDERR_FILENO, "unsetenv: missing argument\n");
	else
	{
		if (unsetenv(args[1]) != 0)
			perror("unsetenv");
	}
}

/**
 * 
*/
void help_command(char **args,  char *NAME, int argc)
{
	(void)NAME, (void)argc;

	if (args[1] == NULL)
	{
		printf("This is a simple shell program.\n");
		printf("                    Supported built-in commands:\n");
		printf("\n/----------------------------------------------------------------------------------------/\n");
		printf("    Name                                        Usage\n");
		printf("\n");
		printf("    cd                                          cd <Directory path>\n");
		printf("    help                                        help\n");
		printf("    exit                                        exit <Enter> or exit Status\n");
		printf("    setenv                                      setenv [NAME] <value>\n");
		printf("    unsetenv                                    unsetenv [NAME]\n");
		printf("\n/---------------------------------------------------------------------------------------/\n");
		printf("    Authors                                     Ebiri ThankGod, Onyedibia Okeomasilachi.\n");
	}
}
