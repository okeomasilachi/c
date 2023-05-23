#include "main.h"

/**
 * B_exc - function handles all command processing
 * @argc: argument count
 * @Name: name of the compiled program [argv[0]]
 * @cmd: commandline input
 * @av: parsed commands
 * @environ: environmental variable
 *
 * Return: void
*/
void B_exc(int argc, char *Name, char *cmd, char **av, char **environ, int ok)
{
	int i, status = 0, y = 0;
	char **command = NULL, *tok;
	Tokenizer token;

	find_char(cmd, '#');
	y = findAndSet(cmd, "&&", "||");
	f_tokenizer(&token, cmd);
	tok = s_tok(&token, "&&||");
	while (tok != NULL)
	{
		command = prs(tok, 1);
		for (i = 0; command[i] != NULL; i++)
		{
			av = prs(command[i], 0);
			status = execute_builtin_command(av, Name, argc);
			if (status != 0)
			{
				status = execute_command(av, environ, 0, Name, argc, ok);
			}
		}
		if (y == 1)
		{
			if (status != 0)
				break;
		}
		if (y == 2)
		{
			if (status == 0)
				break;
		}
		y = findAndSet(NULL, "&&", "||");
		tok = s_tok(&token, "&&||");
	}
}

/**
 * find_executable - finds the path of an execuitable if it exist
 * @argv: variable to search for
 *
 * Return: pointer to the variable on success
 * error: NULL
*/
char *find_executable(char *argv)
{
	char *path_env, *path_copy, *token, *exe_path;
	size_t token_len, exec_name_len;
	Tokenizer Hook;

	if (access(argv, X_OK) == 0)
	{
		exe_path = _strdup(argv);
		return (exe_path);
	}
	path_env = _getenv("PATH");
	path_copy = _strdup(path_env);
	f_tokenizer(&Hook, path_copy);
	token = s_tok(&Hook, ":");
	while (token)
	{
		token_len = _strlen(token);
		exec_name_len = _strlen(argv);
		exe_path = (char *)malloc((token_len + exec_name_len + 2) * sizeof(char));
		if (exe_path == NULL)
		{
			perror("Memory allocation failed");
			_free(1, path_copy);
			return (NULL);
		}
		_strcpy(exe_path, token);
		_strcat(exe_path, "/");
		_strcat(exe_path, argv);
		if (access(exe_path, X_OK) == 0)
		{
			_free(1, path_copy);
			return (exe_path);
		}
		_free(1, exe_path);
		token = s_tok(&Hook, ":");
	}
	_free(1, path_copy);
	return (NULL);
}

/**
 * execute_command - executes the command
 * @args: commands to be eexcuited;
 * @envp: environmental variable
 * @n: set for executable name [argv[0]]
 * @Name: name of the compiled program
 * @argc: argument count
 *
 * Return: 0 on success
 * error: non zero value
*/
int execute_command(char **args, char **envp, size_t n, char *Name, int argc, int i)
{
	char *ec;
	pid_t child_pid;
	int status;

	(void)argc;
	ec = find_executable(args[n]);
	if (!ec)
	{
		pf(STDERR_FILENO, "%s: %d: %s: not found\n", Name, i, args[n]);
		return (EXIT_FAILURE);
	}

	if (ec)
	{
		child_pid = fork();
		if (child_pid == -1)
			perror("fork");

		else if (child_pid == 0)
		{
			execve(ec, args, envp);
			return (EXIT_FAILURE);
		}
		else
		{
			waitpid(child_pid, &status, 0);
			if (WIFEXITED(status))
			{
				return (WEXITSTATUS(status));
			}
		}
	}
	return (-1);
}
