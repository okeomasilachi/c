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

int findAndSet(char* str, const char* searchStr1, const char* searchStr2) {
    static char* currentPosition = NULL;
    static int setValue = 0;
    char *result1, *result2;

    if (str != NULL) {
        currentPosition = str;
        setValue = 0;
    }

    if (currentPosition == NULL) {
        printf("Invalid input. Please provide a string to search.\n");
        return -1;
    }

    result1 = searchStr1 != NULL ? strstr(currentPosition, searchStr1) : NULL;
    result2 = searchStr2 != NULL ? strstr(currentPosition, searchStr2) : NULL;

    if (result1 == NULL && result2 == NULL) {
        return -1;
    }

    if (result1 == NULL || (result2 != NULL && result2 < result1)) {
        currentPosition = result2 + strlen(searchStr2);
        setValue = 2;
    } else {
        currentPosition = result1 + strlen(searchStr1);
        setValue = 1;
    }

    return setValue;
}

/*char *intToString(int number) {
    int num = number, length = 0, isNegative = 0, index;
    char *str = NULL;

    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    do {
        length++;
        num /= 10;
    } while (num != 0);

    str = (char*)malloc((length + isNegative + 1) * sizeof(char));
    if (str == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    index = length + isNegative - 1;
    do {
        str[index] = '0' + (number % 10);
        number /= 10;
        index--;
    } while (number != 0);

    if (isNegative) {
        str[0] = '-';
    }

    str[length + isNegative] = '\0';

    return str;
}

int count(const char *haystack, const char *needle) {
    int count = 0;
    size_t needleLen = strlen(needle);

    while (*haystack) {
        if (strncmp(haystack, needle, needleLen) == 0) {
            count++;
            haystack += needleLen; 
        } else {
            haystack++;
        }
    }

    return count;
}*/
