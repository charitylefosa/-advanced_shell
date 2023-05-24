#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include "main.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
extern char *__progname;

/*
*print_prompt - displays prompt for user to type command
*/
void print_prompt(void)
{
	printf("$ ");
}
/**
*read_command - awaits command and reads it
*@command: command line user inputs
*Return:1 if successful
*	0 if unsuccessful
*/
int read_command(char *command)
{
	if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
	{
		return (0);
	}
	return (1);
}

/**
*remove_newline - removes newline after command
*@command: command line user inputs
*/
void remove_newline(char *command)
{
	size_t len = strlen(command);

	if (len > 0 && command[len - 1] == '\n')
	{
		command[len - 1] = '\0';
	}
}

/**
*parse_arguments - handles arguments in a command
*@command: command line user input
*@arguments: arguments to be executed in the command
*Return: argument parsed number
*/
int parse_arguments(char *command, char *arguments[])
{
	int i = 0;
	char *token;

	token = strtok(command, " ");

	while (token != NULL && i < MAX_ARGUMENTS - 1)
	{
		arguments[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	arguments[i] = NULL;
	return (i);
}

/**
*execute_command - executes commands
*@arguments: arguments to be executed in the command
*/
void execute_command(char *arguments[])
{
	pid_t pid;
	int status;
	int input_fd;

	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Error: Fork failed.\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (arguments[0] != NULL && arguments[1] != NULL
				&& strcmp(arguments[1], "<") == 0)
		{
			input_fd = open(arguments[2], O_RDONLY);
			if (input_fd < 0)
			{
				fprintf(stderr, "Error:Failure to open file '%s'.\n", arguments[2]);
				exit(EXIT_FAILURE);
			}
			if (dup2(input_fd, STDIN_FILENO) < 0)
			{
				fprintf(stderr, "Error: Command not found.\n");
				exit(EXIT_FAILURE);
			}
			close(input_fd);
			arguments[1] = NULL;
		}
		execvp(arguments[0], arguments);
		fprintf(stderr, "Error: Command not found.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	printf("$\n");
	fflush(stdout);
}
