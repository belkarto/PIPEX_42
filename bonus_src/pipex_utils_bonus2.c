/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:37:04 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/19 08:32:35 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child_p(t_pip pip, char **env)
{
	close(pip.fd[0]);
	dup2(pip.fd_infile, STDIN_FILENO);
	close(pip.fd_infile);
	dup2(pip.fd[1], STDOUT_FILENO);
	close(pip.fd[1]);
	check(execve(pip.path[0], pip.cmd[0], env), __FILE__, __LINE__);
}

void	second_child_pros(t_pip pip, char **env, int argc, char **argv)
{
	close(pip.fd[1]);
	pip.fd_outfile = check(open(argv[argc - 1], 2 | O_CREAT, 0644),
			__FILE__, __LINE__);
	dup2(pip.fd[0], STDIN_FILENO);
	close(pip.fd[0]);
	dup2(pip.fd_outfile, STDOUT_FILENO);
	close(pip.fd_outfile);
	execve(pip.path[1], pip.cmd[1], env);
}
