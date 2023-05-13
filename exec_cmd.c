#include "main.h"

struct built_in b_s[] = {
    {"exit", exit_func},
    {"cd", _cd},
    {"setenv", _setenv},
    {"unsetenv", _unsetenv},
};

char* find_executable(char *argv)
{
	char *path_env, *path_copy, *token, *executable_path;
	size_t token_len, exec_name_len;

    path_env = getenv("PATH");
    path_copy = strdup(path_env);
    token = strtok(path_copy, ":");

    while (token != NULL) {
        token_len = strlen(token);
        exec_name_len = strlen(argv);
        executable_path = (char*)malloc((token_len + exec_name_len + 2) * sizeof(char));

        if (executable_path == NULL) {
            perror("Memory allocation failed");
            free(path_copy);
            return NULL;
        }

        strcpy(executable_path, token);
        strcat(executable_path, "/");
        strcat(executable_path, argv);

        if (access(executable_path, X_OK) == 0) {
            free(path_copy);
            return executable_path;
        }

        free(executable_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}


void execute_command(char** args, char** envp, size_t n, char *Name, int argc)
{
	char *ec;
    pid_t child_pid;
    int status, i;

    /*Execute the command by calling execve()*/
    for (i = 0; i < num_B_in(); i++)
    {
        if (strcmp(args[0], b_s[i].command) == 0)
        {
            b_s->func(args);
        }
    }
    ec = find_executable(args[n]);
    if (ec == NULL)
    {
	    dprintf(STDERR_FILENO, "%s: %d: %s: not found\n", Name, argc, args[n]);
    }
    else
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error:");
        }
        if (child_pid == 0)
        {
            execve(ec, args, envp);
    	    perror("Command execution failed");
    	    exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(child_pid, &status, 0);
        }
    }
}

int num_B_in()
{
	return (sizeof(b_s) / sizeof(struct built_in));
}

void exit_func(char **args)
{
	if (args[1] == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	else if (args[1] != NULL)
	{
		exit(atoi(args[1]));
	}
}

void _cd(char **args)
{
	const char *home = getenv("HOME");

    if (args[1] == NULL)
    {
        if (home == NULL)
            dprintf(STDERR_FILENO, "cd: Home directory not found\n");

        if (home)
            chdir(home);
    }
    else
    {
        chdir(args[1]);
    }
}

void _setenv(char **args)
{
    if (args[1] != NULL && args[2] != NULL)
        setenv(args[1], args[2], 1);
}

void _unsetenv(char **args)
{
    if (args[1] != NULL)
        unsetenv(args[1]);
}
