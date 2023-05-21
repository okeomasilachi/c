#include "main.h"

/**
 * 
*/
int open_file(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror("open");
	return (fd);
}

/**
 * 
*/
char *read_lines(int fd)
{
	char *file_contents = NULL, buffer[BUFFER_SIZE];
	size_t file_size = 0;
	ssize_t bytes_read;
	
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		file_contents = _realloc(file_contents, file_size + bytes_read + 1);
		if (file_contents == NULL)
		{
			close(fd);
			return (NULL);
		}
		_memcpy(file_contents + file_size, buffer, bytes_read);
		file_size += bytes_read;
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	if (file_size > 0)
	{
		file_contents = _realloc(file_contents, file_size + 1);
		if (file_contents == NULL)
		{
			close(fd);
			return (NULL);
		}
		file_contents[file_size] = '\0';
	}
	close(fd);
	return (file_contents);
}

/**
 * 
*/
char *read_file(const char *filename)
{
	int fd;
	char *content;

	fd = open_file(filename);
	if (fd == -1)
		return (NULL);
	content = read_lines(fd);
	return (content);
}

/**
 * 
*/
void file_process(char **argv, char **av, char *cmd, char *Name, int argc)
{
	size_t read;

	cmd = read_file(argv[1]);
	/* Remove trailing newline character, if any */
	read = strlen(cmd);
	if (read > 0 && cmd[read - 1] == '\n')
		cmd[read - 1] = '\0';

	B_exc(argc, Name, cmd, av, environ);
	exit(EXIT_SUCCESS);
}
