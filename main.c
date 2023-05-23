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
	int i = 0;

	if (access(argv[1], F_OK) == 0 && argc == 2)
	{
		Name = argv[1];
		file_process(argv, av, cmd, Name, argc, i);
	}
	if (argv[1] != NULL)
	{
		pf(2, "%s: %d: cannot open %s: No such file\n", Name, 0, argv[1]);
		exit(EXIT_SUCCESS);
	}

	if (int_active && argv[1] == NULL)
	{
		while (true)
		{
			i++;
			pf(STDOUT_FILENO, "($) ");
			cmd = p_Input();
			B_exc(argc, Name, cmd, av, environ, i);
		}
		_free(3, cmd, Name, av);
		exit(EXIT_SUCCESS);
	}
	else
	{
		cmd = p_Input();
		B_exc_2(argc, Name, cmd, av, environ, i);
	}

	return (0);
}
