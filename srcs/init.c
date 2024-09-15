/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:37:43 by dkreise           #+#    #+#             */
/*   Updated: 2023/12/26 18:01:20 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

t_cmd	*new_cmd(char *str, t_struct *cmd_struct)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_error(NULL, "memory allocation error", cmd_struct, 1);
	new->args = ft_split(str, ' ');
	if (!(new->args))
		exit_error(NULL, "memory allocation error", cmd_struct, 1);
	new->next = NULL;
	return (new);
}

t_cmd	*fill_cmd_list(t_struct *cmd_struct)
{
	t_cmd	*first;
	t_cmd	*cmd;
	t_cmd	*new;
	int		i;

	i = 0;
	first = new_cmd(cmd_struct->s_argv[2], cmd_struct);
	first->num = 2;
	cmd = first;
	while (i < cmd_struct->cmd_cnt - 1)
	{
		new = new_cmd(cmd_struct->s_argv[3 + i], cmd_struct);
		new->num = i + 3;
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

t_struct	init_struct(int argc, char **argv, char **env)
{
	t_struct	cmd_struct;

	cmd_struct.s_argc = argc;
	cmd_struct.s_argv = argv;
	cmd_struct.s_env = env;
	cmd_struct.cmd_cnt = argc - 3;
	cmd_struct.paths = get_paths(env);
	cmd_struct.first = fill_cmd_list(&cmd_struct);
	cmd_struct.error = 0;
	return (cmd_struct);
}
