#include "main.h"

/**
 * f_tokenizer - the initializer for string tokenization
 * @tokenizer: struct for storing the tokens
 * @input_string: string to tokenize
 *
 * Return: void
*/
void f_tokenizer(Tokenizer *tokenizer, char *input_string)
{
	tokenizer->cur_tok_st = input_string;
	tokenizer->nxt_tok_st = input_string;
}

/**
 * s_tok - function for tokenizing strings
 * @tokenizer: struct where token are stored
 * @delimeters: the delimeters for the tokenization
 *
 * Return: pointer to token
 * error: NULL if no more tokens are found
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
	tokenizer->nxt_tok_st += _strcspn(tokenizer->nxt_tok_st, delimiters);
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

/**
 * find_char - finds the specified character in a string
 * @str: string to be searched
 * @search: character to search for
 *
 * Return: 0 on success:
 * error: non zero value
*/
int find_char(char *str, char search)
{
	char *str_cpy = strchr(str, search);
	
	if (str == NULL || search == '\0')
	{
		dprintf(STDERR_FILENO, "find_char: missing arguments");
		return (-1);
	}
	
	if (str_cpy != NULL)
	{
		*str_cpy = '\0';
		return (0);
	}
	return (1);
}

/**
 * findAndSet - find two strings in a particular string
 * @str: string to be searched
 * @searchStr1: first string to search for
 * @searchStr2: second string to search for
 *
 * Return: number signifying the case found at a point
*/
int findAndSet(char* str, const char* searchStr1, const char* searchStr2)
{
	static char* currentPosition = NULL;
	static int setValue = 0;
	char *result1, *result2;
	
	if (str != NULL)
	{
		currentPosition = str;
		setValue = 0;
	}
	if (currentPosition == NULL)
	{
		pf(STDERR_FILENO, "Invalid input. Please provide a string to search.\n");
		return (-1);
	}
	result1 = searchStr1 != NULL ? _strstr(currentPosition, searchStr1) : NULL;
	result2 = searchStr2 != NULL ? _strstr(currentPosition, searchStr2) : NULL;
	if (result1 == NULL && result2 == NULL)
		return (-1);

	if (result1 == NULL || (result2 != NULL && result2 < result1))
	{
		currentPosition = result2 + _strlen(searchStr2);
		setValue = 2;
	}
	else
	{
		currentPosition = result1 + _strlen(searchStr1);
		setValue = 1;
	}
	return (setValue);
}

/**
 * _strcpy - copies string
 *
 * @dest: updatd string
 * @src: string copy
 *
 * Return: returns dest
 */

char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	
	return (dest);
}

