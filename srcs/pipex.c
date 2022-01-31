/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:02:45 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/01 00:05:48 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_set_child(t_cmd *cmd, int *pfd)
{
	int	ffd;

	close(pfd[0]);
	if (cmd->file_out)
	{
		ffd = open_file_out(cmd->file_out);
		if (ffd < 0)
		{
			free(cmd->path);
			cmd->path = 0;
		}
		dup2(ffd, STDOUT_FILENO);
		close(ffd);
		close(pfd[1]);
	}
	else
		dup2(pfd[1], STDOUT_FILENO);
}

int	pipex_child(t_cmd *cmd, t_cmd **cmd_lst)
{
	pid_t	pid;
	int		pfd[2];
	int		exit_code;

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		pipex_set_child(cmd, pfd);
		exit_code = 127;
		if (cmd->path)
		{
			execve(cmd->path, cmd->argv, cmd->envp);
			exit_code = errno;
		}
		cmd_del_lst(cmd_lst);
		exit(exit_code);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
	}
	return (pid);
}

int	pipex(t_cmd **cmd_lst)
{
	int		i;
	int		status;
	int		ffd;
	pid_t	pid;

	i = 0;
	while (cmd_lst[i])
	{
		if (cmd_lst[i]->file_in)
		{
			ffd = open_file_in(cmd_lst[i]->file_in);
			dup2(ffd, STDIN_FILENO);
			close(ffd);
		}
		pid = pipex_child(cmd_lst[i], cmd_lst);
		i++;
	}
	waitpid(pid, &status, 0);
	cmd_del_lst(cmd_lst);
	return (WEXITSTATUS(status));
}
