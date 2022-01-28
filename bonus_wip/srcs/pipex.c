/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:18:15 by agiraude          #+#    #+#             */
/*   Updated: 2022/01/27 20:45:54 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	child(t_childset *setting, t_cmd **cmd, int cmdid)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork :");
		return (1);
	}
	if (pid == 0)
	{
		dup2(setting->fd_in, 0);
		dup2(setting->fd_out, 1);
		close(setting->close_in);
		close(setting->close_out);
		if (cmd[cmdid]->path)
		{
			execve(cmd[cmdid]->path, cmd[cmdid]->argv, cmd[cmdid]->envp);
			perror(cmd[cmdid]->path);
			cmd_free_all(cmd);
			exit(errno);
		}
		cmd_free_all(cmd);
		exit(127);
	}
	return (pid);
}

void	set_setting(t_childset *setting, int fd_in, int fd_out, int close_in, int close_out)
{
	setting->fd_in = fd_in;
	setting->fd_out = fd_out;
	setting->close_in = close_in;
	setting->close_out = close_out;
}

int		pipex(int file_in, int file_out, t_cmd **cmd)
{
	t_childset	setting;
	int		pipefd[2];
	pid_t	pids[2];
	int		status[2];

	pipe(pipefd);
	set_setting(&setting, file_in, pipefd[1], file_in, pipefd[0]);
	pids[0] = child(&setting, cmd, 0);
	set_setting(&setting, pipefd[0], file_out, pipefd[1], file_out);
	pids[1] = child(&setting, cmd, 1);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pids[0], &status[0], 0);
	waitpid(pids[1], &status[1], 0);
	cmd_free_all(cmd);
	return (WEXITSTATUS(status[1]));
i}
