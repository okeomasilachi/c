#include "main.h"

int main(int argc, char **argv)
{
    char *cmd = NULL, **av = NULL;
    size_t n = 0;
    ssize_t br = 0;
    int i;
    
    /* Check if av[1] is a file */	
    if (argc == 2 && access(argv[1], F_OK) == 0 && argv[3] != NULL)
    {
        file_process(argv, av, cmd);
    }
    else if (argv[1] != NULL)
    {
        /* Input from command-line arguments */
        execute_command(argv, environ, 1);
    }
    else
    {
        /* Interactive mode */
        while (true)
        {
            printf("$ ");
            br = getline(&cmd, &n, stdin);
            if (br == -1 || cmd[0] == '\n')
                break;

            av = prs(cmd);
            execute_command(av, environ, 0);
            for (i = 0; av[i] != NULL; i++)
                free(av[i]);

            free(av);
        }
    }
    free(cmd);
    return EXIT_SUCCESS;
}
