#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int	main()
{
	char	**envp;
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
			args[0] = line;
			args[1] = NULL;
			//this is just for test
			//printf("line = %s\nline size = %lu\n", line, line_size);
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

