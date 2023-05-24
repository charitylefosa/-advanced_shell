#include "main.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64

/**
*run_interactive_mode - runs the shell in interactive mode until
*the "exit" command is entered.
*/

void run_interactive_mode(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *arguments[MAX_ARGUMENTS];
	int running = 1;
	int num_arguments;

	while (running)
	{
		print_prompt();
		if (!read_command(command))
		{
			break;
		}
		remove_newline(command);
		if (strcmp(command, "exit") == 0)
		{
			running = 0;
		}
		else if (strcmp(command, "env") == 0)
		{
			char **env = environ;

			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
		}
		else
		{
			num_arguments = parse_arguments(command, arguments);

			if (num_arguments > 0)
			{
				execute_command(arguments);
			}
		}
	}
}

/**
*run_non_interactive_mode - runs the shell in non_interactive mode until
*the "exit" command is entered.
*@input_file: the file to read commands from
*/
void run_non_interactive_mode(FILE *input_file)
{
	char command[MAX_COMMAND_LENGTH];
	char *arguments[MAX_ARGUMENTS];
	int num_arguments;

	while (fgets(command, MAX_COMMAND_LENGTH, input_file) != NULL)
	{
		remove_newline(command);

		if (strcmp(command, "exit") == 0)
		{
			break;
		}
		else if (strcmp(command, "env") == 0)
		{
			char **env = environ;

			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
		}
		else
		{
			num_arguments = parse_arguments(command, arguments);
			if (num_arguments > 0)
			{
				execute_command(arguments);
			}
		}
	}
}

/**
*main - pront is printed, user imputs command, arguments
*in the command are executed and give output, exit
*command is to exit the shell.
*@argc: argument count
*@argv: argument vector
*Return: Always 0
*/
int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		FILE *input_file = fopen(argv[1], "r");

		if (input_file == NULL)
		{
			fprintf(stderr, "Error: Failed to open file '%s'.\n", argv[1]);
			return (EXIT_FAILURE);
		}
		run_non_interactive_mode(input_file);
		fclose(input_file);
	}
	else
	{
		run_interactive_mode();
	}
	return (EXIT_SUCCESS);
}
