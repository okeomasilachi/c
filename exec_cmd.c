#include "main.h"

/**
 *
*/
void B_exc(int argc, char *Name, char *cmd, char **av, char **environ)
{
	int i, j, status = 0, y = 0;
	char **command = NULL, *tok, *cmdy = NULL;

	(void)j;
	cmdy = strdup(cmd);
	y = findAndSet(cmdy, "&&", "||");
	tok = strtok(cmd, "&&||");
	while (tok != NULL)
	{
		command = prs(tok, 1);
		for (i = 0; command[i] != NULL; i++)
		{
			/*if (av != NULL)
			{
				for (j = 0; av[j] != NULL; j++)
					free(av[i]);
				free(av);
			}*/
			av = prs(command[i], 0);
			if ((status = execute_builtin_command(av,Name,argc)) != 0)
			{
				status = execute_command(av, environ,0,Name,argc);
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
		y = findAndSet(NULL,"&&", "||");
		tok = strtok(NULL, "&&||");
	}
}


/**
 * 
*/
char *find_executable(char *argv)
{
	char *path_env, *path_copy, *token, *executable_path;
	size_t token_len, exec_name_len;
	Tokenizer Hook;

	if (access(argv, X_OK) == 0)
 	{
 	       executable_path = strdup(argv);
 	       return executable_path;
	}
	path_env = getenv("PATH");
	path_copy = strdup(path_env);
	f_tokenizer(&Hook, path_copy);
	token = s_tok(&Hook, ":");
	while (token)
	{
		token_len = strlen(token);
		exec_name_len = strlen(argv);
		executable_path = (char *)malloc((token_len + exec_name_len + 2) * sizeof(char));
		if (executable_path == NULL)
		{
			perror("Memory allocation failed");
			free(path_copy);
			return (NULL);
		}
		strcpy(executable_path, token);
		strcat(executable_path, "/");
		strcat(executable_path, argv);
		if (access(executable_path, X_OK) == 0)
		{
			free(path_copy);
			return (executable_path);
		}
		free(executable_path);
		token = s_tok(&Hook, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * 
*/
int execute_command(char **args, char **envp, size_t n, char *Name, int argc)
{
	char *ec;
	pid_t child_pid;
	int status;
	ec = find_executable(args[n]);
	if (!ec)
	{
		pf(STDERR_FILENO, "%s: %d: %s: not found\n", Name, argc, args[n]);
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
