/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:01:36 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/08 01:57:35 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/fcntl.h>
#include <sys/wait.h>
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

int	main(int argc, char *argv[])
{
	int	fd[2];
	int	pid, pid2;
	int fd1;
	char	*cmd;
	char	**args;

	args = ft_split(argv[1], ' ');
	cmd = ft_strjoin("/bin/", args[0]);
	check(pipe(fd), __FILE__, __LINE__);
	pid = check(fork(), __FILE__, __LINE__);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		check(execve(cmd, args, NULL), __FILE__, __LINE__);
	}
	pid2 = check(fork(), __FILE__, __LINE__);
	if (pid2 == 0)
	{
		fd1 = check(open(argv[argc - 1], 2 | O_CREAT, 0644), __FILE__, __LINE__);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd1, STDOUT_FILENO);
		close(fd1);
		close(fd[0]);
		close(fd[1]);
		args = ft_split(argv[2], ' ');
		cmd = ft_strjoin("/bin/", args[0]);
		execve("/bin/cat", args, NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
