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
	int		fd_infile;
	char	**cmd;
	char	**path;
}	t_pip;

int	check(int x, char *file, int line);
void	ft_free(char **str);
#endif
