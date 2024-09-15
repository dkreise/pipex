/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:41:29 by dkreise           #+#    #+#             */
/*   Updated: 2023/12/23 18:26:09 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define NONE 0
# define FIRST 1
# define SECOND 2
# define BOTH 3
# define NOENV "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applicat\
ions/VMware Fusion.app/Contents/Public:/usr/local/go/bin:/usr/local/munki"

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*next;
	int				num;
}				t_cmd;

typedef struct s_struct
{
	t_cmd	*first;
	char	**paths;
	int		cmd_cnt;
	int		s_argc;
	char	**s_argv;
	char	**s_env;
	int		error;
}				t_struct;

t_struct	init_struct(int argc, char **argv, char **env);
void		do_dups(int c, int *pipefd, t_struct *cmd_struct);
void		free_struct(t_struct *cmd_struct);
void		exit_error(char *arg, char *msg, t_struct *c_struct, int exit_code);
void		do_execve(t_struct *c_struct, t_cmd *cmd);

#endif
