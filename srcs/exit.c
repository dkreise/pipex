/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:47:20 by dkreise           #+#    #+#             */
/*   Updated: 2023/12/28 17:07:18 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_paths(t_struct *cmd_struct)
{
	int	i;

	i = 0;
	if (cmd_struct->paths)
	{
		while (cmd_struct->paths[i])
		{
			free(cmd_struct->paths[i]);
			i ++;
		}
		free(cmd_struct->paths);
	}
}

void	free_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i ++;
		}
		free(cmd->args);
	}
}

void	free_struct(t_struct *cmd_struct)
{
	t_cmd	*cmd;
	t_cmd	*cmd_next;

	if (cmd_struct)
	{
		free_paths(cmd_struct);
		cmd = cmd_struct->first;
		while (cmd)
		{
			cmd_next = cmd->next;
			free_args(cmd);
			free(cmd);
			cmd = cmd_next;
		}
	}
}

void	exit_error(char *arg, char *msg, t_struct *c_struct, int exit_code)
{
	write(2, "pipex: ", ft_strlen("pipex: "));
	if (msg)
	{
		if (arg)
		{
			write(2, arg, ft_strlen(arg));
			write(2, ": ", 2);
		}
		write(2, msg, ft_strlen(msg));
	}
	else
		perror(arg);
	free_struct(c_struct);
	exit(exit_code);
}

void	do_execve(t_struct *c_struct, t_cmd *cmd)
{
	char	*path;
	int		i;

	i = 0;
	execve(cmd->args[0], cmd->args, c_struct->s_env);
	if (c_struct->paths)
	{
		while (c_struct->paths[i])
		{
			path = ft_strjoin(ft_strjoin(c_struct->paths[i], "/", NONE),
					cmd->args[0], FIRST);
			if (!path)
				exit_error(NULL, "memory allocation error\n", c_struct, 1);
			execve(path, cmd->args, c_struct->s_env);
			free(path);
			i ++;
		}
	}
	exit_error(c_struct->s_argv[cmd->num],
		"command not found\n", c_struct, 127);
}
