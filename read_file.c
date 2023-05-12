#include "main.h"

int open_file(const char* filename)
{
	int fd;
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
	}
	return (fd);
}

char* read_lines(int fd)
{
	char *line = NULL, buffer[BUFFER_SIZE];
	ssize_t bytes_read, i, line_length = 0;
	
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		for (i = 0; i < bytes_read; i++)
		{
			if (buffer[i] == '\n')
			{
				line = realloc(line, line_length + i + 2);
				if (line == NULL) /* error from relloc */
				{
					close(fd);
					return (NULL);
				}
				memcpy(line + line_length, buffer, i + 1);
				line[line_length + i + 1] = '\0';
				line_length = 0;
				memmove(buffer, buffer + i + 1, bytes_read - i - 1);
				close(fd);
				return (line);
			}
		}
		line_length += bytes_read;
	}
	if (line_length > 0)
	{
		line = realloc(line, line_length + 1);
		if (line == NULL) /* error from relloc */
		{
			close(fd);
			return (NULL);
		}
		memcpy(line + line_length, buffer, line_length);
		line[line_length] = '\0';
	}
	close(fd);
	return (line);
}


char* read_file(const char* filename)
{
	int fd;
	char *content;

	fd = open_file(filename);
	if (fd == -1)
	{
		return (NULL);
	}
	content = read_lines(fd);
	return (content);
}

void file_process(char **argv, char **av, char *cmd, char *Name, int argc)
{
	size_t read;
	int i;

	cmd = read_file(argv[1]);
        /* Remove trailing newline character, if any */
        read = strlen(cmd);
	    if (read > 0 && cmd[read - 1] == '\n')
		    cmd[read - 1] = '\0';

        av = prs(cmd);
	execute_command(av, environ, 0, Name, argc);
        for (i = 0; av[i] != NULL; i++)
		free(av[i]);

        free(av);
	cmd = NULL;
}

int is_executable(char *argv) {
    struct stat st;
    char *path;

    /* Get file status */
    path = find_executable(argv);
    if (stat(path, &st) == -1) {
        perror("Failed to get file status");
        return 0;
    }

    /* Check if the file is executable */
    if (st.st_mode & S_IXUSR)
        return 1;

    return 0;
}
