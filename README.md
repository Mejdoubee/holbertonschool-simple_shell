# Simple Shell

A simple shell implementation in C.

## Description

This simple shell is a command-line interface for executing system commands. It supports running commands in both interactive and non-interactive modes, and it can search for the commands in the system's `PATH`. The shell handles command execution, argument parsing, and some built-in commands such as `exit`.

## Features

- Interactive and non-interactive modes
- Command parsing and execution
- Built-in `exit` command
- Searches for commands in the system's `PATH`

## Compilation

To compile the simple shell, run:

```bash
gcc -o simple_shell *.c -Wall -Werror -Wextra -pedantic
```

This will create an executable named `simple_shell`.

## Usage

To run the simple shell in interactive mode, execute:

```bash
./simple_shell
```

In interactive mode, the shell will display a prompt (`#cisfun$ `) and wait for user input. Type a command and press Enter to execute it. To exit the shell, type `exit` and press Enter.

To run the simple shell in non-interactive mode, execute:


```bash
echo "command" | ./simple_shell

```

or

```bash
cat commands.txt | ./hsh
```

Replace `command` with the command you want to execute. The shell will execute the command and exit.

## Functions

- `main`: The main function for the simple shell.
- `read_line`: Reads a line from stdin.
- `get_command_path`: Searches for the command in the system's `PATH` and returns the command's path if found.
- `execute`: Executes a command with the given arguments and environment variables.
- `parse_commands`: Parses a line into an array of commands.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
