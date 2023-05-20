#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define MAX_AL 100
#define MAX_AL_N_L 50
#define MAX_AL_V_L 100

extern char **environ;

/*---------------------------------------------------------------*/
/* for tokenization of strings */

/**
 * 
*/
typedef struct
{
	char *cur_tok_st;
	char *nxt_tok_st;
} Tokenizer, o_tok;

typedef struct main
{
	char name[MAX_AL_N_L];
	char value[MAX_AL_V_L];
}alias;




/* call the f_tokenizer function before using s_tok function passing in the parameters */
void f_tokenizer(Tokenizer *tokenizer, char *input_string);
char *s_tok(Tokenizer *tokenizer, const char *delimiters);
char **prs(char *command, size_t del_n);
/*--------------------------------------------------------------*/
int open_file(const char *filename);
char *read_lines(int fd);
char *read_file(const char *filename);
void file_process(char **argv, char **av, char *cmd, char *Name, int argc);
/*--------------------------------------------------------------*/
int execute_command(char **args, char **envp, size_t n, char *Name, int argc);
char *find_executable(char *argv);
/*---------------------------------------------------------------*/
void cd_command(char **args, char *NAME, int argc);
void exit_command(char **args, char *NAME, int argc);
void setenv_command(char **args, char *NAME, int argc);
void unsetenv_command(char **args, char *NAME, int argc);
void help_command(char **args, char *NAME, int argc);
int execute_builtin_command(char **args, char *NAME, int argc);

/**
 * 
*/
struct built_in
{
	char *name;
	void (*function)(char **args, char *NAME, int argc);
};
/*--------------------------------------------------------------------------*/
int B_exc(int argc, char *Name, char *cmd, char **av, char **environ);
void read_input(void);
char *_getline(void);
/*--------------------------------------------------------------------------*/
void pf(int stream, const char *format, ...);
void write_string(int n, const char *s);
void print_integer(int num, int n);
void print_string(char *s, int n);
void parseArs_alias(char **args, char *NAME, int argc);
void def_alias(char *name, char *value);
void print_S_alias(char *names[], int numNames);
void p_all_alias(void);
#endif /* MAIN_H */
