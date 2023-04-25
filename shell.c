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
	char **args;
	int interactive = 1;

	(void)argc;
	(void)argv;

	args = malloc(sizeof(char *) * 2);
	args[1] = NULL;

	if (isatty(STDIN_FILENO) == 0)
	{
		interactive = 0;
	}

	while (1)
	{
		if (interactive)
		{
			printf("#cisfun$ ");
		}
		line = read_line();
		if (line == NULL)
		{
			if (feof(stdin))
			{
				break;
			}
			continue;
		}

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		command_path = get_command_path(line);
		if (command_path == NULL)
		{
			printf("%s: No such file or directory\n", line);
			free (line);
			if (!interactive)
			{
				break;
			}
			continue;
		}

		args[0] = command_path;
		execute(command_path, args, envp);
		free(line);
		if (command_path != line)
		{
			free(command_path);
		}
		if (!interactive)
		{
			continue;
		}
	}
	free(args);
	return (0);
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

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
		{
			command_path = command;
		}
		else
		{
			char bin_path[] = "/bin/";
			command_path = malloc(strlen(bin_path) + strlen(command) + 1);
			strcpy(command_path, bin_path);
			strcat(command_path, command);
			if (access(command_path, X_OK) != 0)
			{
				free(command_path);
				command_path = NULL;
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
