/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:32:20 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/19 16:13:00 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include "stdio.h"

int		run_child_1(int file_in, char *cmd_path, char **cmd_arg, int *pipefd)
{
	dup2(file_in, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(file_in);
	execve(cmd_path, cmd_arg, 0);
	exit(0);
}

int		run_child_2(int file_out, char *cmd_path, char **cmd_arg, int *pipefd)
{
	dup2(file_out, 1);
	dup2(pipefd[0], 0);
	close(pipefd[1]);
	close(file_out);
	execve(cmd_path, cmd_arg, 0);
	exit(0);
}

void	pipex(int file_in, int file_out, char **argv, char **envp)
{
	int	pipefd[2];
	int	status;
	char	**cmd_1;
	char	**cmd_2;
	pid_t	child_1;
	pid_t	child_2;


	cmd_1 = ft_split(argv[2], ' ');
	cmd_2 = ft_split(argv[3], ' ');
	pipe(pipefd);
	child_1 = fork();
	if (child_1 < 0)
		return (perror("Fork: "));
	if (child_1 == 0)
		run_child_1(file_in, generate_path(envp, cmd_1[0]), cmd_1, pipefd);
	child_2 = fork();
	if (child_2 < 0)
		return (perror("Fork: "));
	if (child_2 == 0)
		run_child_2(file_out, generate_path(envp, cmd_2[0]), cmd_2, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child_1, &status, 0);
	waitpid(child_2, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	file_in;
	int	file_out;

	file_in = open(argv[1], O_RDONLY);
	file_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file_in < 0 || file_out < 0)
		return (-1);
	pipex(file_in, file_out, argv, envp);
	return (0);
}
