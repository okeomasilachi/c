#include "main.h"

/**
 * _strcpy - copies string
 *
 * @dest: updatd string
 * @src: string copy
 *
 * Return: returns dest
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
