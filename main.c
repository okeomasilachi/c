#include "main.h"

int main(int argc, char **argv)
{
    char *cmd = NULL, **av = NULL;
    size_t n = 0;
    int i;
    
    /* Check if av[1] is a file */	
    if (argc == 2 && access(argv[1], F_OK) == 0)
    {
        file_process(argv, av, cmd);
    }
    else if (argc >= 2)
    {
        /* Input from command-line arguments */
	    i = 0;
        while (i != argc)
	    {
	    	puts(argv[i]);
	    	i++;
	    }
    }
    else
    {
        /* Interactive mode */
        while (true)
        {
            printf("$ ");
            getline(&cmd, &n, stdin);
            av = prs(cmd);
            for (i = 0; av[i] != NULL; i++)
                free(av[i]);

            free(av);
        }
    }
    free(cmd);
    return EXIT_SUCCESS;
}
