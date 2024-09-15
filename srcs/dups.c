/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:42:03 by dkreise           #+#    #+#             */
/*   Updated: 2023/12/27 20:55:58 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	dup_first(int f1, int *pipefd)
{
	pipe(pipefd);
	dup2(f1, STDIN_FILENO);
	close(f1);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
}

void	dup_last(int f2, int *pipefd)
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	dup2(f2, STDOUT_FILENO);
	close(f2);
}

void	dup_rest(int *pipefd)
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	pipe(pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
}

void	do_dups(int c, int *pipefd, t_struct *cmd_struct)
{
	int	f1;
	int	f2;

	if (c == 0)
	{
		f1 = open(cmd_struct->s_argv[1], O_RDONLY);
		if (f1 == -1)
		{
			write(2, "pipex: ", ft_strlen("pipex: "));
			perror(cmd_struct->s_argv[1]);
			cmd_struct->error = 1;
		}
		dup_first(f1, pipefd);
	}
	else if (c == cmd_struct->cmd_cnt - 1)
	{
		f2 = open(cmd_struct->s_argv[cmd_struct->s_argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (f2 == -1)
			exit_error(cmd_struct->s_argv[cmd_struct->s_argc - 1],
				NULL, cmd_struct, 1);
		dup_last(f2, pipefd);
	}
	else
		dup_rest(pipefd);
}
