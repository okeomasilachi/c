#include "main.h"

char **prs(char *command)
{
	char *com_cpy = NULL, *tok, *dl = " \t\n\r";
	Tokenizer tokens;
	size_t count = 0, cnt = 0;
	char **av = NULL;

	if (command)
	{
		com_cpy = strdup(command);
		f_tokenizer(&tokens, command);
		tok = s_tok(&tokens, dl);
		
		while (tok)
		{
			cnt++;
			tok = s_tok(&tokens, dl);
		}
		cnt++;

		av = malloc(sizeof(char *) * (cnt + 1));
		f_tokenizer(&tokens, com_cpy);
		tok = s_tok(&tokens, dl);
		while (tok)
		{
			av[count] = malloc(sizeof(char) * (strlen(tok) + 1));
			strcpy(av[count], tok);
			tok = s_tok(&tokens, dl);
			count++;
		}
		av[count] = NULL;
		free(com_cpy);
		com_cpy = NULL;
		count = 0, cnt = 0;
	}
	return (av);
}


void reallocate(char **args, char **av, int argc)
{
	int i;
	
	for (i = 0; av[i] != NULL; i++)
	{
		free(av[i]);
	}
	free(av);

	av = malloc(sizeof(char *) * argc);
	i = 1;
	while (args[i] != NULL)
	{
		av[i - 1] = malloc(sizeof(char) * strlen(args[i]) + 1);
		strcpy(av[i - 1], args[i]);
		i++;
	}
	av[i - 1] = NULL;
}