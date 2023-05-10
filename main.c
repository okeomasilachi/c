#include "main.h"

int main(int ac, char **av)
{
	char *cmd = NULL;
	size_t n = 0, i;

	(void)ac;

	while (true)
	{
		printf("$ ");
		getline(&cmd, &n, stdin);
		av = prs(cmd);

		for (i = 0; av[i] != NULL; i++)
		{
			free(av[i]);
		}
		free(av);
		av = NULL;
	}
	free(cmd);
	return (EXIT_SUCCESS);
}
