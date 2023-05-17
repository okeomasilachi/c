#include "main.h"

int main(int argc, char **argv)
{
    char *cmd = NULL, **av = NULL, *Name = argv[0], **command = NULL;
    size_t n = 0;
    ssize_t br = 0;

    if (argc == 2 && access(argv[1], F_OK) == 0 && access(argv[1], X_OK) != 0)
    {
	file_process(argv, av, cmd, Name, argc);
    }

    if (argc == 1 && argv[1] == NULL)
    {
	do {
		write(STDOUT_FILENO, "$ ", 2);
	        br = getline(&cmd, &n, stdin);
	        if (br == EOF) 
	            break;
	        if (cmd[0] == '\n') continue;
	        command = prs(cmd, 1);
		B_exc(argc, Name, command, av, environ);
	} while(true && !argv[1] && argc <= 1);
	free(cmd);
	exit(EXIT_SUCCESS);
    }
	return 0;

}
