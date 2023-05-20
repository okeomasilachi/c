#include "main.h"

/**
 *
*/
int B_exc(int argc, char *Name, char *cmd, char **av, char **environ)
{
	int j, r;

	av = prs(cmd, 0);
	if (!execute_builtin_command(av, Name, argc))
	{
		r = execute_command(av, environ, 0, Name, argc);
	}

	for (j = 0; av[j] != NULL; j++)
		free(av[j]);
	free(av);

	/*for (i = 0; command[i] != NULL; i++)
	{
		av = prs(command[i], 0);
		if (!execute_builtin_command(av, Name, argc))
		{
			r = execute_command(av, environ, 0, Name, argc);
		}

		for (j = 0; av[j] != NULL; j++)
			free(av[j]);
		free(av);
	}*/
	return (r);
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
	if (ec == NULL)
	{
		pf(STDERR_FILENO, "%s: %d: %s: not found\n", Name, argc, args[n]);
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
			perror("fork");

		else if (child_pid == 0)
		{
			execve(ec, args, envp);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(child_pid, &status, 0);
			if (WIFEXITED(status))
			{
				return (WEXITSTATUS(status));
			}
		}

		return (-1);
	}
	return (-1);
}
