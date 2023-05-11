#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

/*---------------------------------------------------------------*/

/* for tokenization of strings */

typedef struct {
    char *cur_tok_st;
    char *nxt_tok_st;
} Tokenizer, o_tok;

/* call the f_tokenizer function before using s_tok function passing in the parameters */
void f_tokenizer(Tokenizer *tokenizer, char *input_string);
char *s_tok(Tokenizer *tokenizer, const char *delimiters);
char **prs(char *command);
/*--------------------------------------------------------------*/
int open_file(const char* filename);
char* read_lines(int fd);
char* read_file(const char* filename);
void file_process(char **argv, char **av, char *cmd);

#endif /* MAIN_H */
