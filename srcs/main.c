/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:48:49 by dkreise           #+#    #+#             */
/*   Updated: 2024/09/15 17:23:38 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	pipex(t_struct *cmd_struct)
{
	int		pid;
	int		status;
	int		pipefd[2];
	int		c;
	t_cmd	*cmd;
	
	status = 0;
	c = -1;
	while (c < cmd_struct->cmd_cnt - 1)
	{
		c ++;
		cmd_struct->error = 0;
		do_dups(c, pipefd, cmd_struct);
		if (c == 0)
			cmd = cmd_struct->first;
		else
			cmd = cmd->next;
		if (cmd_struct->error != 0)
			continue ;
		pid = fork();
		if (pid == 0)
			do_execve(cmd_struct, cmd);
	}
	if (pid != 0)
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	main(int argc, char	**argv, char *env[])
{
	t_struct	cmd_struct;
	int			exit_status;

	(void)env;
	if (argc != 5)
		exit_error(NULL, "invalid number of arguments\n", NULL, 1);
	cmd_struct = init_struct(argc, argv, env);
	exit_status = pipex(&cmd_struct);
	free_struct(&cmd_struct);
	return (exit_status);
}
