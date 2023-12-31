#include "shell.h"

/**
 * _strcpy - Copy a string.
 * @dest: The destination.
 * @src: The source.
 *
 * Return: Pointer to the destination.
 */
char *_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

/**
 * _strdup - Duplicate a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *duplicate;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	duplicate = malloc(sizeof(char) * (length + 1));

	if (!duplicate)
		return (NULL);

	for (length++; length--;)
		duplicate[length] = *--str;

	return (duplicate);
}

/**
 * _puts - Print an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * _putchar - Write the character 'c' to stdout.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buffer[index++] = c;

	return (1);
}

