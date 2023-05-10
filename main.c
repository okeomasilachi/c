#include "main.h"

int main(int argc, char **argv)
{
    char *cmd = NULL, **av;
    size_t n = 0, read;
    int i;
    
    /* Check if av[1] is a file */	
    if (argc == 2 && access(argv[1], F_OK) == 0)
    {
        cmd = read_file(argv[1]);
        /* Remove trailing newline character, if any */
        read = strlen(cmd);
	if (read > 0 && cmd[read - 1] == '\n')
		cmd[read - 1] = '\0';

        av = prs(cmd);
        for (i = 0; av[i] != NULL; i++)
		free(av[i]);

        free(av);
	cmd = NULL;
    }
    else if (argc >= 2)
    {
        /* Input from command-line arguments */
	i = 0;
        while (argv[i] != NULL)
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
