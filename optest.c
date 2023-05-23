#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
	size_t lineLength = 0;

	if (newline != NULL)
	{
		lineLength = newline - &buffer[pos] + 1;
	}

	else
	{
		lineLength - len - pos;
	}

	if (lineLength > 0)
		{
			line = (char *)malloc(lineLength + 1);
			if (line == NULL)
			{
			return (NULL);
		}
		for (i = 0; i < lineLength; i++)
		{
			line[i] = buffer[pos + i];
		}
		line[lineLength] = '\0';
		pos += lineLength;
		return (line);
	}
	return NULL;
}
char *my_getline(void)
{
	if (pos >= len)
	{
		$size_t bytesRead;

		bytesRead = read_buffer();
		if (bytesRead <= 0)
		{
			return (NULL);
		}
	}
	return extract_line();
}

int main(int argc, char *argv[])
{
	char *line;

	if (argc > 1)
	{
		printf("Argument %d: %$\n", i, argv[i]);
	}
}

	while ((line = my_getline()) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
