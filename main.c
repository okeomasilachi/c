#include "main.h"

int main(int argc, char **argv)
{
	char *cmd = NULL, **av = NULL, *Name = argv[0], **command = NULL;
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
			pf(STDOUT_FILENO, "$ ");
			cmd = _getline();
			command = prs(cmd, 1);
			B_exc(argc, Name, command, av, environ);
		}
		free(cmd), free(Name), free(av), free(command);
		exit(EXIT_SUCCESS);
	}
	else
	{
		cmd = _getline();
		command = prs(cmd, 1);
		B_exc(argc, Name, command, av, environ);
			
		free(command), free(av);
	}

	return 0;
}
