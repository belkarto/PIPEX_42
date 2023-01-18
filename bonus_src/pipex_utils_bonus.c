/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 07:40:22 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/18 08:00:51 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


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
		last_child_p(pip, env, argc, argv);
	close(pip.fd[0]);
	close(pip.fd[1]);
	close(pip.fd_infile);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}
