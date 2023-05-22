#ifndef PRS_H
#define PRS_H

#include "main.h"
/**
 * struct me - Built in's of the shell
*/
me built_in_commands[] = {
	{"cd", cd_command},
	{"exit", exit_command},
	{"setenv", setenv_command},
	{"unsetenv", unsetenv_command},
	{"help", help_command}
};

struct read
{
	static char buffer[BUFFER_SIZE];
	static int buffer_pos;
	static int buffer_size;
}
#endif /* PRS_H */