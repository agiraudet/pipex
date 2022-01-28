/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:31:53 by agiraude          #+#    #+#             */
/*   Updated: 2022/01/23 13:38:18 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	strlst_free(char **strlst)
{
	int	i;

	i = 0;
	while(strlst[i])
		free(strlst[i++]);
	free(strlst);
}

char	*path_sanitize_cmd(char *base_cmd)
{
	char *correct_cmd;
	char **wip_cmd;

	wip_cmd = ft_split(base_cmd, ' ');
	correct_cmd = ft_strjoin("/", wip_cmd[0]);
	strlst_free(wip_cmd);
	return (correct_cmd);
}	

char	*path_check(char **env_paths, char *cmd)
{
	char	*pathname;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));

	cmd = path_sanitize_cmd(cmd);
	i = 0;
	while (env_paths[i])
	{
		pathname = ft_strjoin(env_paths[i], cmd);
		if (access(pathname, X_OK) == 0)
		{
			free(cmd);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	pathname = ft_strdup(&cmd[1]);
	free(cmd);
	return (pathname);
}

char	*path_for_cmd(char *cmd, char **envp)
{
	char	*fail;
	char	*pathname;
	char	**env_paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			env_paths = ft_split(&envp[i][5], ':');
		i++;
	}
	pathname = path_check(env_paths, cmd);
	strlst_free(env_paths);
	if (!pathname)
	{
		fail = ft_strjoin(cmd, ": command not found");
		error_msg(fail, 0);
		free(fail);
		return (0);
	}
	return (pathname);
}
