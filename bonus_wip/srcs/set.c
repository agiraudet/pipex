/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:01:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/01/23 14:52:40 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		cmd_check(char *cmd)
{
	if (cmd[0] != '.' && ft_strchr(cmd, '/') == 0 && access(cmd, X_OK) != 0)
	{
		error_format("TEST: ", cmd, ": command not found");
		return (0);
	}
	return (1);
}

t_cmd	*cmd_create(char *cmdline, char **envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->argv = ft_split(cmdline, ' ');
	cmd->path = path_for_cmd(cmd->argv[0], envp);
	if (!cmd_check(cmd->path))
	{
		free(cmd->path);
		cmd->path = 0;
	}
	cmd->envp = envp;
	return (cmd);
}

void	cmd_free_all(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if(cmd[i]->path)
			free(cmd[i]->path);
		strlst_free(cmd[i]->argv);
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

t_cmd	**cmd_set_all(int argc, char **argv, char **envp)
{
	t_cmd	**cmd;

	cmd = (t_cmd **)malloc(sizeof(t_cmd *) * argc - 2);
	cmd[0] = cmd_create(argv[2], envp);
	cmd[1] = cmd_create(argv[3], envp);
	cmd[2] = 0;
	return (cmd);
}
