#include "main.h"

#include "main.h"

/**
 * unget_char - ungets a character
 * @src: character to unget
 *
 * Return: void
 */

void unget_char(struct source_s *src)
{
	if (src->curpos < 0)
	{
		return;
	}
	src->curpos--;
}

/**
 * next_char - Gets the next character
 * @src: the character to get
 *
 * Return: character
 */

char next_char(struct source_s *src)
{
	char c1 = 0;
	(void)c1;

	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (-ERRCHAR);
	}

	if (src->curpos == INIT_SRC_POS)
	{
		src->curpos  = -1;
	}
	else
	{
		c1 = src->buffer[src->curpos];
	}

	if (++src->curpos >= src->bufsize)
	{
		src->curpos = src->bufsize;
		return (EOF);
	}

	return (src->buffer[src->curpos]);
}

/**
 * peek_char - peeks to see the next character to get
 * @src: peek character
 *
 * Return: character
 */

char peek_char(struct source_s *src)
{
	long pos;

	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (-ERRCHAR);
	}

	pos = src->curpos;
	if (pos == INIT_SRC_POS)
	{
		pos++;
	}

	pos++;
	if (pos >= src->bufsize)
	{
		return (EOF);
	}
	return (src->buffer[pos]);
}

/**
 * skip_white_spaces - skips white spaces in a string
 * @src: the source string
 *
 * Return: void
 */

void skip_white_spaces(struct source_s *src)
{
	char c;

	if (!src || !src->buffer)
	{
		return;
	}

	while (((c = peek_char(src)) != EOF) && (c == ' ' || c == '\t'))
	{
		next_char(src);
	}
}
