#include "main.h"

/**
 * 
*/
void f_tokenizer(Tokenizer *tokenizer, char *input_string)
{
	tokenizer->cur_tok_st = input_string;
	tokenizer->nxt_tok_st = input_string;
}

/**
 * 
*/
char *s_tok(Tokenizer *tokenizer, const char *delimiters)
{
	char *token;

	if (tokenizer->cur_tok_st == NULL)
		return (NULL);
	/* Skip leading delimiters */
	tokenizer->cur_tok_st += strspn(tokenizer->cur_tok_st, delimiters);
	/* Check if end of string is reached */
	if (*tokenizer->cur_tok_st == '\0')
	{
		tokenizer->cur_tok_st = NULL;
		return (NULL);
	}
	tokenizer->nxt_tok_st = tokenizer->cur_tok_st;
	/* Find the end of the current token */
	tokenizer->nxt_tok_st += strcspn(tokenizer->nxt_tok_st, delimiters);
	if (*tokenizer->nxt_tok_st != '\0')
	{
		*tokenizer->nxt_tok_st = '\0';
		tokenizer->nxt_tok_st++;
	}
	else
	{
		tokenizer->nxt_tok_st = NULL;
	}
	token = tokenizer->cur_tok_st;
	tokenizer->cur_tok_st = tokenizer->nxt_tok_st;

	return (token);
}
