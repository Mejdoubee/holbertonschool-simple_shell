#ifndef SHELLHEADER_H
#define SHELLHEADER_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

char *read_line();
char *get_command_path(char *command);
int execute(char *command_path, char **args, char **envp);

#endif
