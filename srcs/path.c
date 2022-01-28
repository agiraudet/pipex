/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 16:45:10 by agiraude          #+#    #+#             */
/*   Updated: 2022/01/21 10:55:46 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

char	*good_path(char **all_path, char *cmd)
{
	char	*pathname;
	int		i;

	cmd = ft_strjoin("/", cmd);
	i = 0;
	while (all_path[i])
	{
		pathname = ft_strjoin(all_path[i], cmd);
		if (access(pathname, X_OK) == 0)
		{
			free(cmd);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	return (0);
}

void	free_srlst(char **strlst)
{
	int	i;

	i = 0;
	while (strlst[i])
		free(strlst[i++]);
}

char	*generate_path(char **envp, char *cmd)
{
	char	**all_path;
	char	*env_path;
	char	*path;
	char	*error;
	int		i;

	i = 0;
	env_path = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			env_path = envp[i];
		i++;
	}
	if (!env_path)
		return (0);
	all_path = ft_split(env_path + 5, ':');
	path = good_path(all_path,cmd);
	free_srlst(all_path);
	if (!path)
	{
		char *errorg= 0;
		error = ft_strjoin("pipex: ", cmd);
		perror(error);
		free(error);
		exit(0);
	}
	return (path);
}
