/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:33:31 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/19 16:12:15 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct	s_child
{
	int		pid;
	int		fd_in;
	int		fd_out;
	int		fd_in_close;
	int		fd_out_close;
	char	*cmd_path;
	char	**cmd_arg;
}	t_child;

char	*generate_path(char **envp, char *cmd);

#endif
