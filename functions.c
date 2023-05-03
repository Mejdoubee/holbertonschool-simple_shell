#include "shellheader.h"

/**
* read_line - Function to read a line from stdin
*
* Return: Return line as strinf
*
*/
char *read_line()
{
	char *line = NULL;
	size_t buffer = 0;

	if (getline(&line, &buffer, stdin) == -1)
	{
		if (feof(stdin))
		{
			if (isatty(STDIN_FILENO))
			{
				printf("\n");
			}
			free(line);
			line = NULL;
		}
		else
		{
			perror("getline");
			exit(1);
		}
	}
	else
	{
		line[strcspn(line, "\n")] = '\0';
	}
	return (line);
}

/**
* get_command_path - Function to get command path
* @command: Command to look for
* Return: Command path if found, NULL if not
*
*/
char *get_command_path(char *command)
{
	char *command_path = NULL, *ptr = NULL;
	char *bin_path = getenv("PATH");
	char *copy_path = NULL, *token = NULL;

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
			command_path = strdup(command);
		else
			perror("access"), command_path = NULL;
	}
	else
	{
		if ((command[0] == '.') && (access(command, X_OK) == 0))
			command_path = strdup(command);
		else if (command[0] != '.')
		{
			if (bin_path)
			{
				copy_path = strdup(bin_path), token = strtok(copy_path, ":");
				while (token)
				{
					ptr = malloc(strlen(token) + strlen(command) + 2);
					strcpy(ptr, token), strcat(ptr, "/"), strcat(ptr, command);
					if (access(ptr, X_OK) == 0)
					{
						command_path = ptr;
						break;
					}
					else
						free(ptr);
					command_path = NULL, token = strtok(NULL, ":");
				}
				free(copy_path);
			}
		}
	}
	return (command_path);
}

/**
* execute - Function thar execute a command
* @command_path: Path to the command to execute
* @args: Arguments for the command
* @envp: Array of env variables
* Return: Return 1 on successful execution
*/
int execute(char *command_path, char **args, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(command_path, args, envp);
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("fork");
		exit(1);
	}
	return (WEXITSTATUS(status));
}

/**
* parse_commands - Parses a line into an array of commands
* @line: The input line to parse
* Return: A pointer to an array of commands
*
*/
char **parse_commands(char *line)
{
	char **commands;
	char *command;
	int count = 0;

	commands = malloc(sizeof(char *) * (strlen(line) + 1));
	if (!commands)
	{
		perror("malloc");
		exit(1);
	}

	command = strtok(line, " \t");
	while (command)
	{
		commands[count++] = command;
		command = strtok(NULL, " \t");
	}
	commands[count] = NULL;

	return (commands);
}
