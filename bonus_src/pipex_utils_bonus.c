/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:22:57 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/19 09:26:13 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"
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

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	**add_slash(char **path)
{
	int		i;
	char	**holder;

	i = 0;
	if (path == NULL)
		return (NULL);
	while (path[i])
		i++;
	holder = (char **)ft_calloc(i + 1, sizeof(char **));
	i = -1;
	while (path[++i])
		holder[i] = ft_strjoin(path[i], "/");
	ft_free(path);
	return (holder);
}

void	child(t_pip pip, char **env, int ind)
{
	int	out;

	out = dup(pip.fd[1]);
	dup2(pip.fd[0], STDIN_FILENO);
	close(pip.fd[0]);
	dup2(out, STDOUT_FILENO);
	close(out);
	close(pip.fd[1]);
	close(pip.fd_infile);
	execve(pip.path[ind +1], pip.cmd[ind + 1], env);
}

void	mid_proc(t_pip pip, char **env, int ac)
{
	int	i;
	int	pid;

	i = -1;
	ac -= 5;
	while (++i < ac)
	{
		pid = check(fork(), __FILE__, __LINE__);
		if (pid == 0)
			child(pip, env, i);
		waitpid(pid, NULL, 0);
	}
}

void	exec_cmd(t_pip pip, char **env, char **argv, int argc)
{
	int	pid;
	int	pid2;

	check(pipe(pip.fd), __FILE__, __LINE__);
	pid = check(fork(), __FILE__, __LINE__);
	if (pid == 0)
		first_child_p(pip, env);
	pid2 = check(fork(), __FILE__, __LINE__);
	if (pid2 == 0)
		second_child_pros(pip, env, argc, argv);
	close(pip.fd[0]);
	close(pip.fd[1]);
	close(pip.fd_infile);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	exec_multi_cmd(t_pip pip, char **env, char **argv, int argc)
{
	int	pid;
	int	pid2;

	check(pipe(pip.fd), __FILE__, __LINE__);
	pid = check(fork(), __FILE__, __LINE__);
	if (pid == 0)
		first_child_p(pip, env);
	mid_proc(pip, env, argc);
	pid2 = check(fork(), __FILE__, __LINE__);
	if (pid2 == 0)
		second_child_pros(pip, env, argc, argv);
	close(pip.fd[0]);
	close(pip.fd[1]);
	close(pip.fd_infile);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}
