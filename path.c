#include "simple_shell.h"

/**
* find_path - finds the path from the global enviroment
* Return: NULL if path is not found or path if path is found.
*/
char *find_path(void)
{
	int i;
	char **env = environ, *path = NULL;

	while (*env)
	{
		if (_strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env;
			while (*path && i < 5)
			{
				path++;
				i++;
			}
			return (path);
		}
		env++;
	}
	return (NULL);
}
