/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:02:43 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/07 21:02:43 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "my_lib/libft.h"
# include <fcntl.h>
# include <errno.h>

typedef struct s_pip {
	int		fd[2];
	int		pid;
	int		pid2;
	int		fd1;
	int		fd_infile;
	int		env_holder;
	char	*cmd;
	char	**args;
	char	**env;
}	t_pip;

int	check(int x, char *file, int line);

#endif
