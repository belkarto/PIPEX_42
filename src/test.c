#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

int	check(int x, char *file, int line)
{
	if (x == -1)
	{
		ft_printf("ERROR : (%s) %d %s\n", file, line, strerror(errno));
		exit (1);
	}
	return (x);
}

int main (int argc, char *argv[])
{
	char	*cmd;
	char	**args;

	args = ft_split(argv[1], ' ');
	cmd = ft_strjoin("/bin/", args[0]);
	system("leaks a.out");
	check(execve(cmd,  args, NULL), __FILE__, __LINE__);
	return 0;
}
