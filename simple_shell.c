#include "simple_shell.h"

#define BUFFER_SIZE 1024

int	main()
{
	char	**envp;
	char	**cmd;
	char	*line = NULL;
	char	*args[2];
	size_t	line_size = 0;

	while (1)
	{
		// Display prompt
		printf("simple_shell$ ");
		// Read user input
		if (getline(&line, &line_size, stdin) == -1)
		{
			// End of file condition
			printf("\n");
			break;
		}
		// Remove trailing newline character
		line[strcspn(line, "\n")] = '\0';
		// Fork process
		pid_t pid = fork();
		if (pid == -1)
		{
			// Fork failed
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// Child process
			cmd = ft_split(line, ' ');
			args[0] = cmd[0];
			args[1] = NULL; //cmd[1]; trying to handle command lines with arguments
			//this is just for test
			// printf("line =%s\nline size = %lu\n", line, line_size);
			// printf("cmd[0] =%s\ncmd[1] = %s\n\n", cmd[0], cmd[1]);
			execve(args[0], args, envp);
			// execve only returns if an error occurs
			perror("Error");
			exit(EXIT_FAILURE);
		}
		else
		{
			// Parent process
			wait(NULL);
		}
	}

	free(line);
	exit(EXIT_SUCCESS);
}

