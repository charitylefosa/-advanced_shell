#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

char *extract_line(void);
ssize_t read_buffer(void);


extern char **environ;
void print_prompt(void);
int read_command(char *command);
void remove_newline(char *command);
int parse_arguments(char *command, char *arguments[]);
void execute_command(char *arguments[]);
void run_interactive_mode(void);
void run_non_interactive_mode(FILE *input_file);
int main(int argc, char *argv[]);

#endif
