/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:40:08 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/20 14:11:29 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

// in pipe we us array of 2
// let's call it fd[2]
// fd[0] is the read end of pipe
// fd[1] is the write end of pipe

char	***fill_cmd(int len, char **av)
{
	int		i;
	char	***cmd;
	int		tracker;

	tracker = 0;
	cmd = (char ***)ft_calloc(sizeof(char **), len + 1);
	i = -1;
	while (++i < len)
		cmd[i] = ft_split(av[i], ' ');
	i = -1;
	while (++i < len)
	{
		if (ft_strlen(cmd[i][0]) != 0 && cmd[i][0][0] == '/')
		{
			tracker = 1;
			ft_printf("no such file or directory : %s\n", cmd[i][0]);
		}
	}
	if (tracker == 1)
		exit(127);
	return (cmd);
}

char	*get_cmd_path(char *cmd, char **path)
{
	char	*holder;
	int		i;

	i = -1;
	if (access(cmd, X_OK) != -1)
	{
		return (cmd);
	}
	while (path[++i])
	{
		holder = ft_strjoin(path[i], cmd);
		if (access(holder, X_OK) != -1)
			return (holder);
		free(holder);
	}
	if (cmd)
		ft_putstr_fd("command not found: %s\n", 2);
	else
		ft_putstr_fd("permission denied:\n", 2);
	return (NULL);
}

// path holdes each command path dependes on its index
// like cmd[0] its path is path[0] and so on
// get path is function that help to get each command path and return 
// 2D arr of paths 

char	**get_path(char ***cmd, char **env, int len)
{
	char	**paths;
	char	**path;
	char	*tmp_path;
	int		i;

	i = -1;
	paths = (char **)ft_calloc(sizeof(char *), len + 1);
	while (env[++i])
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			tmp_path = env[i] + 5;
	path = ft_split(tmp_path, ':');
	path = add_slash(path);
	i = -1;
	while (++i < len)
		paths[i] = get_cmd_path(cmd[i][0], path);
	ft_free(path);
	i = -1;
	while (++i < len)
		if (paths[i] == NULL)
			exit (126);
	return (paths);
}

void	get_cmd(t_pip *pip, int ac, char **av, char **env)
{
	int	i;

	pip->cmd = fill_cmd(ac - 3, av + 2);
	pip->path = get_path(pip->cmd, env, (ac - 3));
	i = -1;
	while (pip->cmd[++i])
	{
		if (ft_strlen(pip->cmd[i][0]) == 0)
			exit (126);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_pip	pip;

	if (argc < 5)
	{
		ft_putstr_fd("not enough argument :\n", 2);
		ft_putstr_fd("\tUSAGE\t: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (2);
	}
	if (argc > 5)
	{
		ft_putstr_fd("too many argument :\n", 2);
		ft_putstr_fd("\tUSAGE\t: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (2);
	}
	pip.fd_infile = check(open(argv[1], O_RDONLY), __FILE__, __LINE__);
	get_cmd(&pip, argc, argv, envp);
	exec_cmd(pip, envp, argv, argc);
	return (0);
}
