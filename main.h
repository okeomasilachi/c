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
#include <limits.h>

#define BUFFER_SIZE 1024

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
void B_exc(int argc, char *Name, char *cmd, char **av, char **environ);
void read_input(void);
char *_getline(void);
/*--------------------------------------------------------------------------*/
void pf(int stream, const char *format, ...);
void write_string(int n, const char *s);
void print_integer(int num, int n);
void print_string(char *s, int n);
int findAndSet(char* str, const char* searchStr1, const char* searchStr2);
/*--------------------------------------------------------------------------*/
void *_memcpy(void *dest, const void *src, size_t n);
void *_memmove(void *dest, const void *src, size_t n);
int _atoi(const char *nptr);
void *_realloc(void *ptr, size_t size);
void _free(int count, ...);
int _setenv(const char *name, const char *value, int overwrite);
char *_getenv(const char *name);
int _unsetenv(const char *name);
int _updateenv(const char *name, const char *value);
int _isdigit(int c);
int _isspace(int c);
/*--------------------------------------------------------------------------*/
char *_strcat(char *dest, char *src);
char *_strchr(char *s, char c);
char *_strncpy(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
char *_strstr(char *haystack, const char *needle);
int _strlen(const char *s);
char *_strdup(const char *s);
int _strncmp(const char s1[], const char s2[], size_t n);
size_t _strcspn(const char *s, const char *reject);
char *_strcpy(char *dest, const char *src);
int find_char(char *str, char search);
#endif /* MAIN_H */
