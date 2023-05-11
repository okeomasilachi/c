#include "main.h"

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


void execute_command(char** args, char** envp, size_t n)
{
	char *ec;
    /*Execute the command by calling execve()*/
    ec = find_executable(args[n]);
    if (ec == NULL)
    {
	dprintf(STDERR_FILENO, "Error: %s : No such command", args[n]);
    }
    else
    {
    	execve(ec, args, envp);
    	perror("Command execution failed");
    	exit(EXIT_FAILURE);
    }
}
