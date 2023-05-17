#include "main.h"

int main(int argc, char **argv)
{
	char *cmd = NULL, **av = NULL, *Name = argv[0], **command = NULL;
	size_t n = 0;
	ssize_t br = 0;
	bool int_active = isatty(STDIN_FILENO);

	if (access(argv[1], F_OK) == 0 && argc == 2)
	{
		file_process(argv, av, cmd, Name, argc);
	}
	else if (int_active)
	{
		while (true)
		{
			write(STDOUT_FILENO, "$ ", 2);
			br = getline(&cmd, &n, stdin);
			if (br == EOF)
			{
				write(STDOUT_FILENO, "\n", 1);
				break;
			}			
			if (cmd[0] == '\n') continue;
			command = prs(cmd, 1);
			B_exc(argc, Name, command, av, environ);
		}
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		br = getline(&cmd, &n, stdin);
		if (br == EOF)
			exit(EXIT_SUCCESS);

		command = prs(cmd, 1);
		B_exc(argc, Name, command, av, environ);
	}
	return 0;
}
