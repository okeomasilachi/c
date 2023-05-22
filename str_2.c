#include "main.h"

/**
 * _isdigit - Checks if variable is a digit.
 * @c: The parameter to be checked.
 *
 * Return: 1 c is a number, 0 otherwise.
 */
int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/**
 * _strlen - gets the length of a string
 * @s: The parameter to be checked.
 *
 * Return: the length of the string;
 */
int _strlen(const char *s)
{
	int length;

	if (s == NULL)
		return (0);
	length = 0;
	while (*s != '\0')
	{
		length++;
		s++;
	}
	return (length);
}

/**
 * _strdup - duplicates a string
 * @s: string to duplicate
 *
 * Return: pointer to the duplicate
*/
char *_strdup(const char *s)
{
	size_t length;
	char *duplicate;

	if (s == NULL)
		return (NULL);
	length = _strlen(s);
	duplicate = (char *) malloc((length + 1) * sizeof(char));
	if (duplicate != NULL)
		_strcpy(duplicate, s);

	return (duplicate);
}

/**
 * _strncmp - compears n bytes of a sring
 * @s1: string to match
 * @s2: string to compare with
 * @n: number of bytes
 *
 * Return: the point where the match case is found
*/
int _strncmp(const char s1[], const char s2[], size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);

		i++;
	}
	if (i == n)
		return (0);

	return (s1[i] - s2[i]);
}

/**
 * _strcspn - returns of initail segments in bytes in s
 * @s: parameter to run calculation on
 * @reject: segments of bytes
 *
 * Return: the segmenth in bytes
*/
size_t _strcspn(const char *s, const char *reject)
{
	size_t length;

	if (s == NULL || reject == NULL)
		return (0);
	length = 0;
	while (s[length] != '\0')
	{
		if (strchr(reject, s[length]) != NULL)
			break;

		length++;
	}
	return (length);
}
