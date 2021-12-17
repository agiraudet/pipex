/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:32:20 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/17 18:00:02 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

char	**parse_cmd(const char *cmd_str)
{
	return (ft_split(cmd_str, ' '));
}

char	***parse_arg(int argc, char **argv, char **file_in_out)
{
	int	i;
	int	ii;
	char	***cmds;

	file_in_out[0] = argv[1];
	file_in_out[1] = argv[argc - 1];
	cmds = (char ***)malloc(sizeof(char **) * argc - 2);
	ii = 0;
	i = 2;
	while (i < argc - 1)
		cmds[ii++] = parse_cmd(argv[i++]);
	cmds[ii] = 0;
	return (cmds);
}	

int	main(int argc, char **argv)
{
	pid_t	child_pid;
	pid_t	wait_result;
	int		stat_loc;
	char	*file_in_out[2];
	char	***cmds;

	if (argc < 5)
		return (0);
	cmds = parse_arg(argc, argv, file_in_out);
	child_pid = fork();
	if (child_pid == 0)
	{
		printf("### CHILD ###\nCurrent PID: %d and child_pid: %d\n", getpid(), child_pid);
	}
	else
	{
		wait_result = waitpid(child_pid, &stat_loc, WUNTRACED);
		printf("### PARENT ###\nCurrent PID: %d and child_pid: %d\n", getpid(), child_pid);
	}
	return (0);
}
