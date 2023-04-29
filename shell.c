#include "shellheader.h"


/**
* main - Main function for the simple shell
* @argc: Argument count
* @argv: Array of argument
* @envp: Array of env variables
* Return: return 0 on successful execution
*/
int main(int argc, char **argv, char **envp)
{
	char *line;
	char *command_path;
	int interactive = 1;
	char **commands;
	int exit_flag = 0;
	int r_code = 0;

	(void)argc;
	(void)argv;

	if (isatty(STDIN_FILENO) == 0)
	{
		interactive = 0;
	}

	while (!exit_flag)
	{
		if (interactive)
		{
			printf("#cisfun$ ");
		}

		line = read_line();
		if (line == NULL)
		{
			if (!interactive)
			{
				break;
			}
			else
			{
				continue;
			}
		}
		commands = parse_commands(line);

		if (commands[0])
		{
			if (strcmp(commands[0], "exit") == 0)
			{
				exit_flag = 1;
			}
			else
			{
				command_path = get_command_path(commands[0]);
				if (command_path == NULL)
				{
					printf("%s: No such file or directory\n", commands[0]);
				}
				else
				{
					execute(command_path, commands, envp);
					if (command_path != commands[0])
					{
						free(command_path);
					}
				}
			}
		}
		free(commands);
		free(line);
		line = NULL;
	}

	return (r_code);
}

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
	char *command_path = NULL;
	char *bin_path = getenv("PATH");
	char *copy_path = NULL;
	char *token = NULL;
	char *ptr = NULL;

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
		{
			command_path = command;
		}
		else
		{
			perror("access");
			command_path = NULL;
		}
	}
	else
	{
		if (access(command, X_OK) == 0)
		{
			command_path = command;
		}
		else
		{
			command_path = NULL;
			copy_path = strdup(bin_path);
			token = strtok(copy_path, ":");
			while (token)
			{
				ptr = malloc(strlen(token) + strlen(command) + 2);
				strcpy(ptr, token);
				strcat(ptr, "/");
				strcat(ptr, command);
				if (access(ptr, X_OK) == 0)
				{
					command_path = ptr;
					break;
				}
				else
				{
					free(ptr);
					command_path = NULL;
				}
				token = strtok(NULL, ":");
			}
			free(copy_path);
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

	pid = fork();
	if (pid == 0)
	{
		execve(command_path, args, envp);
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		perror("fork");
		exit(1);
	}
	return (1);
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