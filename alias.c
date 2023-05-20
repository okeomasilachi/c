#include "main.h"
/*
alias aliases[MAX_AL];
int num_alias = 0;

void p_all_alias(void)
{
	int i;

	if (num_alias == 0)
	{
		pf(STDOUT_FILENO, "No aliases defined\n");
		return;
	}
	for (i = 0; i < num_alias; i++)
		pf(STDOUT_FILENO, "%s='%s'\n", aliases[i].name, aliases[i].value);

}

void print_S_alias(char *names[], int numNames)
{
	int i, j, f;

	if (num_alias == 0)
	{
		pf(STDOUT_FILENO, "No aliases defined\n");
		return;	
	}

	for (i = 0; i < numNames; i++)
	{
		for (j = 0; i < num_alias; j++)
		{
			if (strcmp(names[i], aliases[j].name) == 0)
			{
				pf(STDOUT_FILENO, "%s='%s'\n", aliases[j].name, aliases[j].value);
				f = 1;
				break;
			}
		}
		if (!f)
			pf(STDERR_FILENO, "Alias %s not found\n", names[i]);
	}
}

void def_alias(char *name, char *value)
{
	int i;

	if (strlen(name) > MAX_AL_N_L -1)
	{
		pf(STDERR_FILENO, "Alias name exceeds the maximum lenght if %d characters\n", MAX_AL_N_L);
		return;
	}
	if (strlen(value) > MAX_AL_V_L -1)
	{
		pf(STDERR_FILENO, "Alias value exceeds the maximum lenght if %d characters\n", MAX_AL_V_L);
		return;
	}

	for (i = 0; i < num_alias; i++)
	{
		if (strcmp(name, aliases[i].name) == 0)
		{
			strcpy(aliases[i].value, value);
			return;
		}
	}

	if (num_alias == MAX_AL)
	{
		pf(STDERR_FILENO, "Maximum number of aliases (%d) reached\n", MAX_AL);
		return;
	}

	strcpy(aliases[num_alias].name, name);
	strcpy(aliases[num_alias].value, value);
	num_alias++;
}

void parseArs_alias(char **args, char *NAME, int argc)
{
	char *arg = args[0], *name, *value;
	char **names = malloc(sizeof(char *));
	int i = 1;
	
	
	(void)NAME;

	if (argc -1 == 1)
		p_all_alias();
	else if (argc -1 == 2)
	{
		if (strcmp(arg, "--help") == 0)
		{
			pf(STDOUT_FILENO, "Usage: alias [name[='value'] ...]\n");
			pf(STDOUT_FILENO, "alias: Prints all aliases, one per line. form name='value'\n");
			pf(STDOUT_FILENO, "alias name[name2 ...]: Prints the aliases name, name2, ... one per line. form name='value'\n");
			pf(STDOUT_FILENO, "alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value\n");
		}
		else
		{
			names[0] = arg;
			print_S_alias(names, 1);
		}
	}
	else
	{
		while (i < argc)
		{
			name = args[1];
			value = strchr(name, '=');
			if  (value != NULL)
			{
				*value = '\0';
				value++;
				def_alias(name, value);
			}
			else
			{
				names[0] = name;
				print_S_alias(names, 1);
			}
			i++;
		}
	}
}
*/