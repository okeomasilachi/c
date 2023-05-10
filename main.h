#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

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

#endif /* MAIN_H */
