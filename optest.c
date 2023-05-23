#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static size_t pos;
static size_t len;
size_t i, lineLength;
char *line;


ssize_t read_buffer(void)
{
	ssize_t bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE);

	if (bytesRead <= 0)
	{
		return (bytesRead);
	}
	pos = 0;
	len = bytesRead;
	return (bytesRead);
}

char *find_newline(void)
{
	for (i = pos; i < len; i++)
	{
		if (buffer[i] == '\n')
		{
			return (&buffer[i]);
		}
	}
	return (NULL);
}

char *extract_line(void)
{
	char *newline = find_newline();

	if (newline != NULL)
	{
		lineLength = newline - &buffer[pos] + 1;
		line = (char *)malloc(lineLength);
		if (line == NULL)
		{
			return (NULL);
		}
		for (i = pos; i < pos + lineLength - 1; i++)
		{
			line[i - pos] = buffer[i];
		}
		line[lineLength - 1] = '\0';
		pos += lineLength;
		return (line);
	}
	else
	{
		lineLength = len - pos;
		line = (char *)malloc(lineLength + 1);
		if (line == NULL)
		{
			return (NULL);
		}
		for (i = pos; i < len; i++)
		{
			line[i - pos] = buffer[i];
		}
		line[lineLength] = '\0';
		pos = len;
		return (line);
	}
}

char *my_getline(void)
{
	if (pos >= len)
	{
		ssize_t bytesRead;

		bytesRead = read_buffer();
		if (bytesRead <= 0)
		{
			return (NULL);
		}
	}
	return (extract_line());
}


int main(void)
{
	char *line;

	while ((line = my_getline()) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
