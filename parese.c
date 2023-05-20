#include "main.h"

/**
 * 
*/
char **prs(char *command, size_t del_n)
{
	char *com_cpy = NULL, *tok, *dl = NULL, **av = NULL;
	Tokenizer tokens;
	size_t count = 0, cnt = 0;

	if (del_n == 0)
		dl = " \t\n\r";

	if (del_n == 1)
		dl = ";\n";
	
	if (del_n == 2)
		dl = "&&\\";

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

/**
 * 
*/
struct built_in built_in_commands[] = {
	{"cd", cd_command},
	{"exit", exit_command},
	{"setenv", setenv_command},
	{"unsetenv", unsetenv_command},
	/*{"alias", parseArs_alias},*/
	{"help", help_command},
};

/**
 * 
*/
int execute_builtin_command(char **args,  char *NAME, int argc)
{
	int num_built_in_commands = sizeof(built_in_commands) / sizeof(struct built_in), i;

	for (i = 0; i < num_built_in_commands; i++)
	{
		if (strcmp(args[0], built_in_commands[i].name) == 0)
		{
			built_in_commands[i].function(args, NAME, argc);
			return (1); /* Command executed */
		}
	}
	return (0); /* Not a built-in command */
}

/* Define a global buffer to hold input read from standard input*/

static char buffer[BUFFER_SIZE];
static int buffer_pos;
static int buffer_size;

/**
 * read_input - reads input from a buffer
 *
 * Return: read inputs
 */

void read_input(void)
{
	fflush(stdout);

	if (buffer_pos >= buffer_size)
	{
		buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (buffer_size == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

		if (buffer_size == 0)
		{
			pf(STDOUT_FILENO, "\n");
			exit(EXIT_SUCCESS);
		}
		buffer_pos = 0;
	}
}


/**
 * _getline - function reads from a buffer
 *
 *Return: the charactersread from the buffer
 */

char *_getline(void)
{
	char *line = NULL;
	int line_size = 0;

	while (1)
	{
		if (buffer_pos >= buffer_size)
		{
			read_input();
		}

		if (buffer[buffer_pos] == '\n')
		{
			buffer_pos++;
			line = realloc(line, line_size + buffer_pos);
			memcpy(line + line_size, buffer, buffer_pos);
			line_size += buffer_pos;
			line[line_size - 1] = '\0';

			return (line);
		}
		buffer_pos++;
	}

	if (line != NULL)
	{
		line = realloc(line, line_size + buffer_pos);
		memcpy(line + line_size, buffer, buffer_pos);
		line_size += buffer_pos;
		line[line_size - 1] = '\0';
	}

	return (line);
}
