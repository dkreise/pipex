/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:48:49 by dkreise           #+#    #+#             */
/*   Updated: 2023/12/28 15:15:07 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

int	pipex(t_struct *cmd_struct)
{
	int		pid;
	int		status;
	int		pipefd[2];
	int		c;
	t_cmd	*cmd;

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

int	pipex_hd(t_struct *cmd_struct)
{
	int	pid;
	int	status;
	int	pipefd[2];
	int	file;

	write_to_pipe(cmd_struct, pipefd);
	dup_rest(pipefd);
	pid = fork();
	if (pid == 0)
		do_execve(cmd_struct, cmd_struct->first);
	file = open(cmd_struct->s_argv[cmd_struct->s_argc - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file == -1)
		exit_error(cmd_struct->s_argv[cmd_struct->s_argc - 1],
			NULL, cmd_struct, 1);
	dup_last(file, pipefd);
	pid = fork();
	if (pid == 0)
		do_execve(cmd_struct, cmd_struct->first->next);
	if (pid != 0)
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	main(int argc, char	**argv, char *env[])
{
	t_struct	cmd_struct;
	int			exit_status;
	int			ind;

	if (argc < 5)
		exit_error(NULL, "invalid number of arguments\n", NULL, 1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc != 6)
			exit_error(NULL, "invalid number of arguments\n", NULL, 1);
		ind = 3;
	}
	else
		ind = 2;
	cmd_struct = init_struct(argc, argv, env, ind);
	if (ind == 3)
		exit_status = pipex_hd(&cmd_struct);
	else
		exit_status = pipex(&cmd_struct);
	free_struct(&cmd_struct);
	return (exit_status);
}
