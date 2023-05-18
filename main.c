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
		dprintf(STDERR_FILENO, "%s: %d: cannot open %s: No such file\n", Name, 0, argv[1]);
		exit(EXIT_SUCCESS);
	}

	if (int_active && argv[1] == NULL)
	{
		while (true)
		{
			write(STDOUT_FILENO, "$ ", 2);
			cmd = _getline();			
			command = prs(cmd, 1);
			while (command)
				printf(command:);
			/*B_exc(argc, Name, command, av, environ);*/
		}
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	else if (!int_active)
	{
		cmd = _getline();
		command = prs(cmd, 1);
		B_exc(argc, Name, command, av, environ);
	}

	
	return 0;
}
