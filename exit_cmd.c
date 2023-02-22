#include "simple_shell.h"

/**
* exit_cmd - handles the exit cmd
* @cmd: tokenized cmd
* @line: input read from stdin
*
* Return: no return
*/
void exit_cmd(char **cmd, char *line)
{
	free(line);
	free_buffers(cmd);
	exit(0);
}
