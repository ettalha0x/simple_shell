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
	char *line = NULL, *pathcommand = NULL, *path = NULL;
	size_t buff_size = 0;
	ssize_t line_size = 0;
	char **command = NULL, **paths = NULL;
	(void)envp, (void)av;
	if (ac < 1)
		return (-1);
	signal(SIGINT, handle_signal);
	while (1)
	{
		free_buffers(command);
		free_buffers(paths);
		free(pathcommand);
		prompt_user();
		line_size = getline(&line, &buff_size, stdin);
		if (line_size < 0)
			break;
		info.ln_count++;
		if (line[line_size - 1] == '\n')
			line[line_size - 1] = '\0';
		command = tokenizer(line);
		if (command == NULL || *command == NULL || **command == '\0')
			continue;
		if (checker(command, line))
			continue;
		path = find_path();
		paths = tokenizer(path);
		pathcommand = test_path(paths, command[0]);
		if (!pathcommand)
			perror(av[0]);
		else
			execution(pathcommand, command);
	}
	if (line_size < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);
	free(line);
	return (0);
}
