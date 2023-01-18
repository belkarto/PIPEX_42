/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 07:38:00 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/18 07:56:23 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H
# include "../my_lib/libft.h"
# include <fcntl.h>
# include <errno.h>

typedef struct s_pip {
	int		fd[2];
	int		fd_infile;
	int		fd_outfile;
	char	***cmd;
	char	**path;
}	t_pip;

int		check(int x, char *file, int line);
void	ft_free(char **str);
char	**add_slash(char **path);
void	exec_cmd(t_pip pip, char **env, char **argv, int argc);
void	exec_multi_cmd(t_pip pip, char **env, char **argv, int argc);
void	first_child_p(t_pip pip, char **env);
void	last_child_p(t_pip pip, char **env, int argc, char **argv);
#endif
