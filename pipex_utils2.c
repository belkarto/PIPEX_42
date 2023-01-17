/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belkarto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:37:04 by belkarto          #+#    #+#             */
/*   Updated: 2023/01/17 16:37:04 by belkarto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child_p(t_pip pip, char **env)
{
	dup2(pip.fd_infile, STDIN_FILENO);
	dup2(pip.fd[1], STDOUT_FILENO);
	check(execve(pip.path[0], pip.cmd[0], env), __FILE__, __LINE__);
	close(pip.fd[0]);
	close(pip.fd_infile);
	close(pip.fd[1]);
}

void	second_child_pros(t_pip pip, char **env, int argc, char **argv)
{
	pip.fd_outfile = check(open(argv[argc - 1], 2 | O_CREAT, 0644),
			__FILE__, __LINE__);
	dup2(pip.fd[0], STDIN_FILENO);
	dup2(pip.fd_outfile, STDOUT_FILENO);
	close(pip.fd_outfile);
	close(pip.fd[0]);
	close(pip.fd[1]);
	execve(pip.path[1], pip.cmd[1], env);
}
