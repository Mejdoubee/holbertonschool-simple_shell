#include "shellheader.h"

/**
* process_commands - Main loop for processing and executing commands
* @interactive: Flag indicating if the shell is running in interactive mode
* @argv: Array of arguments
* @envp: Array of environment variables
* Return: Return code of the command execution
*/
int process_commands(int interactive, char **argv, char **envp)
{
	char *line, *command_path;
	int exit_flag = 0, r_code = 0;
	char **commands;

	while (!exit_flag)
	{
		if (interactive)
		{
			printf("#cisfun$ ");
		}
		line = read_line();
		if (line == NULL && !interactive)
		{
			break;
		}
		commands = parse_commands(line);
		if (commands[0])
		{
			if (exit_builtin(commands[0]))
				exit_flag = 1;
			else if (env_builtin(commands[0], envp))
			{
			}
			else
			{
				command_path = get_command_path(commands[0]);
				if (command_path == NULL)
				{
					fprintf(stderr, "%s: 1: %s: not found\n", argv[0], commands[0]);
					r_code = 127;
				}
				else
					execute(command_path, commands, envp), free(command_path);
			}
		}
		free(commands), free(line);
	}
		return (r_code);
}

/**
* exit_builtin - Checks if the given command is the 'exit' command
* @command: The command to check
* Return: 1 if the command is 'exit', 0 otherwise
*
*/
int exit_builtin(char *command)
{
	if (strcmp(command, "exit") == 0)
	{
		return (1);
	}
	return (0);
}

/**
* env_builtin - Checks if the given command is the 'env' command and\
*					prints environment variables if it is
* @command: The command to check
* @envp: Array of environment variables
* Return: 1 if the command is 'env', 0 otherwise
*
*/
int env_builtin(char *command, char **envp)
{
	int i = 0;

	if (strcmp(command, "env") == 0)
	{
		for (; envp[i]; i++)
		{
			printf("%s\n", envp[i]);
		}
		return (1);
	}
	return (0);
}
