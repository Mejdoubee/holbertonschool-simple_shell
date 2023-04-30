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
		if (line == NULL)
		{
			if (!interactive)
				break;
		}
		commands = parse_commands(line);
		if (commands[0])
		{
			if (strcmp(commands[0], "exit") == 0)
				exit_flag = 1;
			else
			{
				command_path = get_command_path(commands[0]);
				if (command_path == NULL)
				{
					fprintf(stderr, "%s: 1: %s: not found\n", argv[0], commands[0]);
					r_code = 127;
				}
				else
				{
					execute(command_path, commands, envp);
					if (command_path != commands[0])
						free(command_path);
				}
			}
		}
		free(commands), free(line), line = NULL;
	}
	return (r_code);
}
