#include "main.h"

int main(int argc, char **argv)
{
    char *cmd = NULL, **av = NULL, *Name = argv[0];
    size_t n = 0;
    ssize_t br = 0;
    int i;
    
    /* Check if av[1] is a file */	
    if (argc == 2 && access(argv[1], F_OK) == 0 && access(argv[1], X_OK) != 0)
    {
        file_process(argv, av, cmd, Name, argc);
    }
    else if (access(argv[1], X_OK) == 0)
    {
        /* Input from command-line arguments */
        execute_command(argv, environ, 1, Name, argc);
    }
    else
    {
        /* Interactive mode */
        while (true)
        {
            printf("$ ");
            br = getline(&cmd, &n, stdin);
            if (br == EOF) 
            {
                putchar('\n');
                break;
            }
            if (cmd[0] == '\n') continue;
            av = prs(cmd);
            execute_command(av, environ, 0, Name, argc);
            for (i = 0; av[i] != NULL; i++)
                free(av[i]);

            free(av);
        }
    }
    free(cmd);
    return EXIT_SUCCESS;
}
