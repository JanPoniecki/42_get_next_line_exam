#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// this functions sticks buffer to the line (buffer is read till \n or till 0)
char	*join_bl(char *buffer, char *line)
{
	int i = 0;
	char *res = calloc(strlen(buffer) + strlen(line) + 2, 1);
	while (line[i])
	{
		res[i] = line[i];
		i ++;
	}
	free(line);
	int j = 0;
	while (buffer[j])
	{
		res[i] = buffer[j];
		if (buffer[j] == '\n')
			break ;
		i ++;
		j ++;
	}
	return res;
}

// this function moves the rest of the buffet (which is not yet returned) to the front
void	move_buffer(char *buffer)
{
	int i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i ++;
	int j = 0;
	while (buffer[i])
	{
		buffer[j] = buffer[i];
		i ++;
		j ++;
	}
	while (buffer[j])
	{
		buffer[j] = 0;
		j ++;
	}
}

// returns next line (not read yet) from given file / or null if nothing is left 
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char	*line;
	char	*n;

	n = NULL;
	line = strdup("");
	while (1)
	{
		n = strchr(buffer, '\n');
		line = join_bl(buffer, line);
		if (n)
			break;
		bzero(buffer, BUFFER_SIZE + 1);
		if (read(fd, buffer, BUFFER_SIZE) <= 0)
			break;
	}
	move_buffer(buffer);
	if (strlen(line) == 0)
	{
		free (line);
		return NULL;
	}
	return line;
}


// main is not the part of the subject but it shows how the functon works
int main()
{
	int bs = BUFFER_SIZE;
	printf("buffer size is %d\n", bs);
	char	*line;
	int		fd;

	fd = open("test", O_RDONLY);
	while (1)
	{
		line = gnl(fd);
		if (!line)
			break ;
		printf("%s", line);
		printf("----------\n");
		free(line);
	}
	return 0;
}
