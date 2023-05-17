#include "main.h"

/**
 *
*/
void B_exc(int argc, char *Name, char **command, char **av, char **environ)
{
	int i;

	for (i = 0; command[i] != NULL; i++)
	{
		av = prs(command[i], 0);
		if (!execute_builtin_command(av, Name, argc))
		{
			execute_command(av, environ, 0, Name, argc);
		}
		for (i = 0; av[i] != NULL; i++)
			free(av[i]);
		free(av);
	}
}
