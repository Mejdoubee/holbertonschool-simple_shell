# Simple Shell

A basic Unix shell written in C, which allows users to execute commands in both interactive and non-interactive modes.

## Features

- Executes commands with their full path or by searching in the `/bin/` directory.
- Supports built-in commands like `exit`.
- Works in both interactive and non-interactive modes.

## Compilation and Usage

To compile the simple shell, run the following command:

\```sh
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
\```

To start the simple shell in interactive mode, run:

\```sh
./hsh
\```

To use the simple shell in non-interactive mode, you can pipe commands or use input redirection, for example:

\```sh
echo "/bin/ls" | ./hsh
\```

or

\```sh
cat commands.txt | ./hsh
\```

## License

This project is released under the MIT License.
# holbertonschool-simple_shell
