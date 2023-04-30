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
	int interactive = 1;
	int r_code = 0;
	(void)argc;
	(void)argv;

	if (isatty(STDIN_FILENO) == 0)
	{
		interactive = 0;
	}
	r_code = process_commands(interactive, argv, envp);
	return (r_code);
}
