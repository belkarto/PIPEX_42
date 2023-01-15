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

void	get_cmd(t_pip *pip, int ac, char **av, char **env)
{
	int	i;

	i = -1;
	pip->cmd = fill_cmd(ac - 3, av + 2);
	ft_printf("%s", pip->cmd[2]);
	(void)av;
	(void)env;
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
	/* if (argc > 5)
	{
		ft_printf("too many argument :\n");
		ft_printf("\tUSAGE\t: %s infile cmd1 cmd2 outfile\n", argv[0]);
		return (2);
	} */
	pip.fd_infile = check(open(argv[1], O_RDONLY), __FILE__, __LINE__);
	get_cmd(&pip, argc, argv, envp);
	return (0);
}
