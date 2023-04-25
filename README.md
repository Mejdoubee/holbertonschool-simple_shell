# Simple Shell

A basic Unix shell written in C, which allows users to execute commands in both interactive and non-interactive modes.

## Features

- Executes commands with their full path or by searching in the `/bin/` directory.
- Supports built-in commands like `exit`.
- Works in both interactive and non-interactive modes.

## Functions

- `main`: The main function that initializes and runs the shell.
- `read_line`: Reads a line from stdin.
- `get_command_path`: Searches for the command path, if not provided as an absolute path.
- `execute`: Executes the command with the given arguments and environment variables.

## Compilation and Usage

To compile the simple shell, run the following command:

```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

To start the simple shell in interactive mode, run:

```
./hsh
```

To use the simple shell in non-interactive mode, you can pipe commands or use input redirection, for example:

```
echo "/bin/ls" | ./hsh
```

or

```
cat commands.txt | ./hsh
```

## License

This project is released under the MIT License.
