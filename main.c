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
#include "pipex.h"
#include <unistd.h>

int	path_checker(char *cmd)
{
	return (0);
}

int	ft_check_cmd(char *cmd, char **env, t_pip *pip)
{
	char	**args;

	args = ft_split(cmd, ' ');
	cmd = args[0];
	if (access(cmd, X_OK) == 0)
		return (1);
	else if (path_checker(cmd) == 0)
		return (2);
	else
		ft_printf("ERROR : (%s)\n\t(%s) %s", __FILE__, cmd, strerror(errno));
	return (0);
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
	pip.fd_infile = check(open(argv[1], 2), __FILE__, __LINE__);
	pip.env_holder = ft_check_cmd(argv[2], envp, &pip);
	return (0);
}
