#include "main.h"

int main(int ac, char **av)
{
	char *cmd = NULL, *cmd_cpy = NULL, *delim = " \n", *tok = NULL;
	size_t n;
	ssize_t nread;
	ac = 0;
	int i;
	
	while (true)
	{
		printf("$ ");
		nread = getline(&cmd, &n, stdin);
		cmd_cpy = strdup(cmd);

		if (nread == -1 || nread == EOF) return -1;

		tok = strtok(cmd, delim);

		while (tok)
		{
			ac++;
			tok = strtok(NULL, delim);
		}
		ac++;

		av = malloc(sizeof(char *) * ac);
		tok = strtok(cmd_cpy, delim);
		while (tok)
		{
			for (i = 0; i < ac + 1; i++)
			{
				av[i + 1] = malloc(sizeof(char) * strlen(tok + 1));
				av[i] = tok;
				puts(av[i]);
				tok = strtok(NULL, delim);
			}
		}
		printf("%s%s", cmd, cmd_cpy);
	}
	free(cmd);
	free(cmd_cpy);
	free(av);
	return (0);
}