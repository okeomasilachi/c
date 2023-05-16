#include "main.h"

int main(int argc, char **argv)
{
    char *cmd = NULL, **av = NULL, *Name = argv[0], **command = NULL;
    size_t n = 0, cmd_length = 0;
    ssize_t br = 0;
    int i;

    if (argc > 1)
    {
	if (argc == 2 && access(argv[1], F_OK) == 0 && access(argv[1], X_OK) != 0)
	        file_process(argv, av, cmd, Name, argc);
	else
	{
		if (argv)
		{
			for (i = 1; i < argc; i++)
		 	   cmd_length += strlen(argv[i]) + 1; /* +1 for space separator */
			cmd = (char*)malloc(cmd_length + 1); /* +1 for null terminator */
			cmd[0] = '\0'; /* Ensuring the string is empty before concatenating */
			for (i = 1; i < argc; i++) {
				strcat(cmd, argv[i]);
				strcat(cmd, " ");
			}		
		}
		command = prs(cmd, 1);
		av = prs(command[i], 0);
		if (!execute_builtin_command(av,Name,argc))
		{
			char *ec;
			if ((ec = find_executable(av[0])) != NULL)
			{
				execve(ec, av, environ);
			}
		}
	}
    }
    else
    {
	while (cmd_length == 0)
	{
		write(STDOUT_FILENO, "$ ", 2);
	        br = getline(&cmd, &n, stdin);
	        if (br == EOF) 
	            break;
	        if (cmd[0] == '\n') continue;
	        command = prs(cmd, 1);
		B_exc(argc, Name, command, av, environ);
	}
    }
    free(cmd);
    return EXIT_SUCCESS;
}
