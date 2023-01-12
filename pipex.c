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

int	main(int argc, char *argv[])
{
	t_pip	pip;
	pip.fd_infile = check(open(argv[1], 2), __FILE__, __LINE__);
	pip.args = ft_split(argv[2], ' ');
	pip.cmd = ft_strjoin("/bin/", pip.args[0]);
	check(pipe(pip.fd), __FILE__, __LINE__);
	pip.pid = check(fork(), __FILE__, __LINE__);
	if (pip.pid == 0)
	{
		dup2(pip.fd[1], STDOUT_FILENO);
		close(pip.fd[0]);
		close(pip.fd[1]);
		check(execve(pip.cmd, pip.args, NULL), __FILE__, __LINE__);
	}
	pip.pid2 = check(fork(), __FILE__, __LINE__);
	if (pip.pid2 == 0)
	{
		pip.fd1 = check(open(argv[argc - 1], 2 | O_CREAT, 0644), __FILE__, __LINE__);
		dup2(pip.fd[0], STDIN_FILENO);
		dup2(pip.fd1, STDOUT_FILENO);
		close(pip.fd1);
		close(pip.fd[0]);
		close(pip.fd[1]);
		pip.args = ft_split(argv[3], ' ');
		pip.cmd = ft_strjoin("/bin/", pip.args[0]);
		execve(pip.cmd, pip.args, NULL);
	}
	close(pip.fd[0]);
	close(pip.fd[1]);
	waitpid(pip.pid, NULL, 0);
	waitpid(pip.pid2, NULL, 0);
	return (0);
}
