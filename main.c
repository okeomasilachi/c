#include "main.h"

int main(int argc, char **argv)
{
    char *cmd = NULL, **av = NULL, *Name = argv[0], *pr;
    size_t n = 0;
    ssize_t br = 0;
    int i;
    
    (void)n;
    /* Check if av[1] is a file */	
    if (argc <= 1)
    {
        /*Interactive mode*/
        while (true)
        {
            char **command = NULL;
            
            pr = "$ ";
            printf("%s", pr);
            br = getline(&cmd, &n, stdin);
            if (br == EOF) 
                break;

            if (cmd[0] == '\n') continue;
            command = prs(cmd, 1);
            
            for (i = 0; command[i] != NULL; i++)
            {
                av = prs(command[i], 0);
                if (!execute_builtin_command(av, Name, argc))
                {
                    execute_command(av, environ, 0, Name, argc);
                }
            }
            for (i = 0; av[i] != NULL; i++)
                    free(av[i]);

            free(av);
        }
            
    }
    else if (argc > 1)
    {
        pr = NULL;
	    if (argc == 2 && access(argv[1], F_OK) == 0 && access(argv[1], X_OK) != 0)
	    {
	            file_process(argv, av, cmd, Name, argc);
	    }
	    else
	    {
            char *com = argv[1];
            char *args[11];
            int arg_c = 0;

            for (i = 1; i < argc; i++)
            {
                args[arg_c++] = argv[i];
            }
            args[arg_c] = NULL;
            exec_command(args, environ, com, Name, argc);
            
	    }
    }
    free(cmd);
    putchar('\n'); 
    return EXIT_SUCCESS;
}
