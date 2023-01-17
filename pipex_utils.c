/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:22:57 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/17 15:37:07 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib/libft.h"
#include "pipex.h"
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

void	first_child_p(t_pip pip, char **env)
{
	dup2(pip.fd_infile, STDIN_FILENO);
	dup2(pip.fd[1], STDOUT_FILENO);
	check(execve(pip.path[0], pip.cmd[0], env), __FILE__, __LINE__);
	close(pip.fd[0]);
	close(pip.fd_infile);
	close(pip.fd[1]);
}

void	second_child_pros(t_pip pip, char **env, int argc, char **argv)
{
	pip.fd_outfile = check(open(argv[argc - 1], 2 | O_CREAT, 0644), __FILE__, __LINE__);
	dup2(pip.fd[0], STDIN_FILENO);
	dup2(pip.fd_outfile, STDOUT_FILENO);
	close(pip.fd_outfile);
	close(pip.fd[0]);
	close(pip.fd[1]);
	execve(pip.path[1], pip.cmd[1], env);
}
void	exec_cmd(t_pip pip, char **env,char **argv, int argc)
{
	int	pid;
	int	pid2;

	check(pipe(pip.fd), __FILE__, __LINE__);
	pid = check(fork(), __FILE__, __LINE__);
	if (pid == 0)
		first_child_p(pip, env);
	pid2 = check(fork(), __FILE__, __LINE__);
	if (pid2 == 0)
	{
		second_child_pros(pip, env, argc, argv);
	}
	close(pip.fd[0]);
	close(pip.fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}
