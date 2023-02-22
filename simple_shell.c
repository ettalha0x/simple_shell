#include "simple_shell.h"
/**
* main - carries out the read, execute then print output loop
* @ac: argument count
* @av: argument vector
* @envp: environment vector
*
* Return: 0
*/

int main(int ac, char **av, char *envp[])
{
	char *line = NULL, *cmd_path = NULL; /* *path = NULL; */
	size_t buff_size = 0;
	ssize_t line_size = 0;
	char **cmd = NULL, **paths = NULL;
	(void)envp, (void)av;
	if (ac < 1)
		return (-1);
	signal(SIGINT, handle_signal);
	while (1)
	{
		free_buffers(cmd);
		//free_buffers(paths);
		free(cmd_path);
		prompt_user();
		line_size = getline(&line, &buff_size, stdin);
		if (line_size < 0)
			break;
		info.ln_count++;
		if (line[line_size - 1] == '\n')
			line[line_size - 1] = '\0';
		cmd = tokenizer(line);
		if (cmd == NULL || *cmd == NULL || **cmd == '\0')
			continue;
		if (checker(cmd, line))
			continue;
		//path = find_path();
		//paths = tokenizer(path);
		cmd_path = cmd[0];
		if (!cmd_path)
			perror(av[0]);
		else
			execute(cmd_path, cmd);
	}
	if (line_size < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);
	free(line);
	return (0);
}
