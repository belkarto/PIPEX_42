/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:40:08 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/11 12:40:10 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_lib/libft.h"
#include "pipex.h"
#include <sys/fcntl.h>
#include <unistd.h>

//function that check if the cmd exist and initialize path_checker
/* int	ft_check_cmd(char *cmd, char **env, char *path)
{
} */

char	**fill_cmd(int len, char **av)
{
	int		i;
	char	**holder;
	char	**cmd;

	cmd = (char **)malloc(sizeof(char *) * len + 1);
	i = -1;
	while(++i < len)
	{
		holder = ft_split(av[i], ' ');
		cmd[i] = ft_strdup(holder[0]);
		ft_free(holder);
	}
	cmd[i] = NULL;
	return (cmd);
}

int	check_pwd(char *cmd, char *pwd, char *holder)
{
	pwd = ft_strjoin_gnl(pwd, "/");
	holder = pwd;
	pwd = ft_strjoin_gnl(pwd, cmd);
	ft_printf("%s \n", pwd);
	(void)holder;
	return (0);
}

int	env_checker(char *cmd, char *env_path, char *holder)
{
	(void)cmd;
		(void)env_path;
		(void)holder;
	return (0);
}

void	ft_check_path(char **cmd, char **path, char *pwd, char *env_path)
{
	int	i;
	char	*path_holder;

	i = -1;
	path_holder = NULL;
	ft_printf("%s\n%s", pwd, env_path);
	while (cmd[++i])
	{
		if (check_pwd(cmd[i], pwd, path_holder) != 0
			&& env_checker(cmd[i], env_path, path_holder) != 0)
		{
			path[i] = path_holder;
		}
		else
		{
			return ;
		}
	}
}

char	**get_path(char **cmd, char **env, int len)
{
	char	**path;
	char	*pwd;
	char	*tmp_path;
	int		i;

	i = -1;
	path = (char **)ft_calloc(sizeof(char *), len + 1);
	while (env[++i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0
			|| ft_strncmp("PWD=", env[i], 4) == 0)
		{
			if (ft_strncmp("PATH=", env[i], 5) == 0)
				tmp_path = ft_strdup(env[i] + 5);
			if (ft_strncmp("PWD=", env[i], 4) == 0)
				pwd = ft_strdup(env[i] + 4);
		}
	}
	ft_check_path(cmd, path, pwd, tmp_path);
	return (path);
}

void	get_cmd(t_pip *pip, int ac, char **av, char **env)
{
	pip->cmd = fill_cmd(ac - 3, av + 2);
	pip->path = get_path(pip->cmd, env, (ac - 3));
}

int	main(int argc, char *argv[], char **envp)
{
	t_pip	pip;

	if (argc < 5)
	{
		ft_printf("not enough argument :\n");
		ft_printf("\tUSAGE\t: %s infile cmd1 cmd2 outfile\n", argv[0]);
		return (2);
	}
	if (argc > 5)
	{
		ft_printf("too many argument :\n");
		ft_printf("\tUSAGE\t: %s infile cmd1 cmd2 outfile\n", argv[0]);
		return (2);
	}
	pip.fd_infile = check(open(argv[1], O_RDONLY), __FILE__, __LINE__);
	get_cmd(&pip, argc, argv, envp);
	return (0);
}
