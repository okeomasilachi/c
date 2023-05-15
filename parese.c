#include "main.h"

char **prs(char *command, size_t k)
{
	char *com_cpy = NULL, *tok, *dl = NULL;
	Tokenizer tokens;
	size_t count = 0, cnt = 0;
	char **av = NULL;

	if (k == 0)
	{
		dl = " \t\n\r";
	}
	else if (k == 1)
	{
		dl = ";\n";
	}
	if (command)
	{
		com_cpy = strdup(command);
		f_tokenizer(&tokens, command);
		tok = s_tok(&tokens, dl);
		
		while (tok)
		{
			cnt++;
			tok = s_tok(&tokens, dl);
		}
		cnt++;

		av = malloc(sizeof(char *) * (cnt + 1));
		f_tokenizer(&tokens, com_cpy);
		tok = s_tok(&tokens, dl);
		while (tok)
		{
			av[count] = malloc(sizeof(char) * (strlen(tok) + 1));
			strcpy(av[count], tok);
			tok = s_tok(&tokens, dl);
			count++;
		}
		av[count] = NULL;
		free(com_cpy);
		com_cpy = NULL;
		count = 0, cnt = 0;
	}
	return (av);
}

struct built_in built_in_commands[] = {
    {"cd", cd_command},
    {"exit", exit_command},
    {"setenv", setenv_command},
    {"unsetenv", unsetenv_command},
    {"help", help_command},
};

/* Implementations of built-in commands */
void cd_command(char** args, char *NAME, int argc) {

    char *ok, *old, *new;
    
    if (args[1] == NULL || strcmp(args[1], "~") == 0 || strcmp(args[1], "-") == 0) {
        if (strcmp(args[1], "-") == 0)
        {
            old = getenv("OLDPWD");
            new = getenv("PWD");
            setenv("OLDPWD", new, 1);
            setenv("PWD", old, 1);
            chdir(old);
            
        }
        else
        {
            ok = getenv("HOME");
            new = getenv("PWD");
            setenv("OLDPWD", new, 1);
            setenv("PWD", ok, 1);
            
            chdir(ok);
        }
              
    } else {

        if (access(args[1], F_OK) != -1)
        {
            ok = getenv("PWD");

            if (chdir(args[1]) == 0) {
                setenv("OLDPWD", ok, 1);
                setenv("PWD", args[1], 1);

            }else {
                dprintf(STDERR_FILENO, "%s: %d: %s: can't cd to %s\n", NAME, argc, args[0], args[1]);
            }
        }
        else
        {
           dprintf(STDERR_FILENO, "%s: %d: %s: not found\n", NAME, argc + 1, args[1]); 
        }
    }
}

void exit_command(char** args, char *NAME, int argc) {
    (void)NAME, (void)argc;
    if (args[1] == NULL)
    {
	exit(EXIT_SUCCESS);
    }
    else if (args[1] != NULL)
    {
	exit(atoi(args[1]));
    }
}

void setenv_command(char** args, char *NAME, int argc) {
    (void)NAME, (void)argc;
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "setenv: missing argument\n");
    } else {
        if (setenv(args[1], args[2], 1) != 0) {
            perror("setenv");
        }
    }
}

void unsetenv_command(char** args,  char *NAME, int argc) {
    (void)NAME, (void)argc;
    if (args[1] == NULL) {
        fprintf(stderr, "unsetenv: missing argument\n");
    } else {
        if (unsetenv(args[1]) != 0) {
            perror("unsetenv");
        }
    }
}

void help_command(char** args,  char *NAME, int argc) {
    
    (void)NAME, (void)argc;
    if (args[1] == NULL)
    {
        printf("This is a simple shell program.\n");
        printf("                    Supported built-in commands:\n");
        printf("\n/----------------------------------------------------------------------------------------/\n");
        printf("    Name                                        Usage\n");
        printf("\n");
        printf("    cd                                          cd <Directory path>\n");
        printf("    help                                        help\n");
        printf("    exit                                        exit <Enter> or exit Status\n");
        printf("    setenv                                      setenv [NAME] <value>\n");
        printf("    unsetenv                                    unsetenv [NAME]\n");
        printf("\n/---------------------------------------------------------------------------------------/\n");
        printf("Authors                                     Ebiri ThankGod, Onyedibia Okeomasilachi.\n");
    }
}

/* Execute the built-in command */
int execute_builtin_command(char** args,  char *NAME, int argc) {
    int num_built_in_commands = sizeof(built_in_commands) / sizeof(struct built_in), i;

    for (i = 0; i < num_built_in_commands; i++) {
        if (strcmp(args[0], built_in_commands[i].name) == 0) {
            built_in_commands[i].function(args, NAME, argc);
            return 1; /* Command executed */
        }
    }

    return 0; /* Not a built-in command */
}