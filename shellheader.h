#ifndef SHELLHEADER_H
#define SHELLHEADER_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>



char *read_line();
char **parse_commands(char *line, int *countsc);
char *trim(char *str);
char *get_command_path(char *command);
void hbtn_ls_wrapper(char *command_path, char **args, char **envp);
int execute(char *command_path, char **args, char **envp);
void copy_ls_to_hbtn_ls();

#endif
