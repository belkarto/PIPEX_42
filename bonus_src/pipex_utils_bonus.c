/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:22:57 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/19 15:12:19 by belkarto         ###   ########.fr       */
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

void	init_cmd(t_pip pip, char **env)
{
	close(pip.fd_pip[0]);
	close(pip.fd[1]);
	dup2(pip.fd[0], STDIN_FILENO);
	close(pip.fd[0]);
	dup2(pip.fd_pip[1], STDOUT_FILENO);
	close(pip.fd_pip[1]);
	check(execve(pip.path[1], pip.cmd[1], env), __FILE__, __LINE__);
}

void	piping(int in[2], int out[2],t_pip pip,  char **env, int i)
{
	close(in[1]);
	close(out[0]);
	dup2(in[0], STDIN_FILENO);
	close(in[0]);
	dup2(out[1], STDOUT_FILENO);
	close(out[1]);
	check(execve(pip.path[i + 1], pip.cmd[i + 1], env), __FILE__, __LINE__);
}

void	child(t_pip pip, char **env, int ind)
{
	if (ind == 0)
		init_cmd(pip, env);
	else if (ind % 2 == 0)
	{
		piping(pip.fd_pip2, pip.fd_pip, pip, env, ind);
	}
	else
	{
		piping(pip.fd_pip, pip.fd_pip2, pip, env, ind);
	}
}

void	last_child(int in[2], t_pip pip, char **env,char ** av, int ac)
{
	close(in[1]);
	dup2(in[0], STDIN_FILENO);
	close(in[0]);
	pip.fd_outfile = check(open(av[ac - 1], 2 | O_CREAT, 0644),
			__FILE__, __LINE__);
	dup2(pip.fd_outfile, STDOUT_FILENO);
	close(pip.fd_outfile);
	execve(pip.path[ac - 1], pip.cmd[ac - 1], env);
}

void	exec_multi_cmd(t_pip pip, char **env, char **argv, int argc)
{
	int	i;
	int	pid;

	i = -1;
	argc -= 5;
	check(pipe(pip.fd_pip), __FILE__, __LINE__);
	check(pipe(pip.fd_pip2), __FILE__, __LINE__);
	while (++i < argc)
	{
		pid = check(fork(), __FILE__, __LINE__);
		if (pid == 0)
			child(pip, env, i);
		waitpid(pid, NULL, 0);
	}
	pid = check(fork(), __FILE__, __LINE__);
	if (pid == 0)
	{
		if (i % 2 == 0)
			last_child(pip.fd_pip, pip, env, argv, argc);
		else
			last_child(pip.fd_pip2, pip, env, argv, argc);
	}
	waitpid(pid, NULL, 0);
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
