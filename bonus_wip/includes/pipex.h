/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:46:40 by agiraude          #+#    #+#             */
/*   Updated: 2022/01/23 14:45:10 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct	s_cmd
{
	char	*path;
	char	**argv;
	char	**envp;
}				t_cmd;

typedef struct	s_childset
{
	int	fd_in;
	int	fd_out;
	int close_in;
	int close_out;
}				t_childset;

//error.c
void	error_format(char *prog_name, char *m1, char *m2);
int	error_ininfile(char *pathname);
int	error_inoutfile(char *pathname);

//pipex.c
int	pipex(int file_in, int file_out, t_cmd **cmd);

//parse.c 
void	strlst_free(char **strlst);
char	*path_for_cmd(char *cmd, char **envp);

//set.c
void	cmd_free_all(t_cmd **cmd);
t_cmd	**cmd_set_all(int argc, char **argv, char **envp);
#endif
