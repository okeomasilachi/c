#include "main.h"

/**
 * main - entry point of the program
 * @argc: argument count
 * @argv: argument variable
 *
 * Return: 0 on success
 * error: non zero value
*/
int main(int argc, char **argv)
{
	char *cmd = NULL, **av = NULL, *Name = argv[0];
	bool int_active = isatty(STDIN_FILENO);


	if (access(argv[1], F_OK) == 0 && argc == 2)
	{
		file_process(argv, av, cmd, Name, argc);
	}
	if (argv[1] != NULL)
	{
		pf(STDERR_FILENO, "%s: %d: cannot open %s: No such file\n", Name, 0, argv[1]);
		exit(EXIT_SUCCESS);
	}

	if (int_active && argv[1] == NULL)
	{
		while (true)
		{
			pf(STDOUT_FILENO, "($) ");
			cmd = _getline();
			B_exc(argc, Name, cmd, av, environ);
		}
		_free(3, cmd, Name, av);
		exit(EXIT_SUCCESS);
	}
	else
	{
		cmd = _getline();
		B_exc(argc, Name, cmd, av, environ);
	}

	return 0;
}
