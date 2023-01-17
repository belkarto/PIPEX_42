/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:22:57 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/15 01:22:57 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
