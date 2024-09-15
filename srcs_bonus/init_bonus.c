/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:37:43 by dkreise           #+#    #+#             */
/*   Updated: 2023/12/28 17:16:11 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

t_cmd	*new_cmd(char *str, t_struct *cmd_struct)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_error(NULL, "memory allocation error\n", cmd_struct, 1);
	new->args = ft_split(str, ' ');
	if (!(new->args))
		exit_error(NULL, "memory allocation error\n", cmd_struct, 1);
	new->next = NULL;
	return (new);
}

t_cmd	*fill_cmd_list(t_struct *cmd_struct, int ind)
{
	t_cmd	*first;
	t_cmd	*cmd;
	t_cmd	*new;
	int		i;

	i = 0;
	first = new_cmd(cmd_struct->s_argv[ind], cmd_struct);
	first->num = ind;
	cmd = first;
	while (i < cmd_struct->cmd_cnt - 1)
	{
		new = new_cmd(cmd_struct->s_argv[ind + 1 + i], cmd_struct);
		new->num = ind + 1 + i;
		cmd->next = new;
		cmd = new;
		i ++;
	}
	return (first);
}

char	**get_paths(char **env)
{
	char	**paths;
	char	**dup_env;

	dup_env = env;
	if (!*env)
		*dup_env = NOENV;
	while (*dup_env)
	{
		if (ft_strncmp(*dup_env, "PATH", 4) != 0)
			dup_env ++;
		else
			break ;
	}
	if (*dup_env)
	{
		while (**dup_env != '/' && **dup_env != '\0')
			(*dup_env)++;
		paths = ft_split(*dup_env, ':');
		if (!paths)
			return (NULL);
		return (paths);
	}
	return (NULL);
}

t_struct	init_struct(int argc, char **argv, char **env, int ind)
{
	t_struct	cmd_struct;

	cmd_struct.s_argc = argc;
	cmd_struct.s_argv = argv;
	cmd_struct.s_env = env;
	cmd_struct.cmd_cnt = argc - ind - 1;
	cmd_struct.paths = get_paths(env);
	cmd_struct.first = fill_cmd_list(&cmd_struct, ind);
	cmd_struct.error = 0;
	return (cmd_struct);
}
