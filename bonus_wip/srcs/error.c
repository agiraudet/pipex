/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:04:06 by agiraude          #+#    #+#             */
/*   Updated: 2022/01/23 14:51:15 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_format(char *prog_name, char *m1, char *m2)
{
	char	*msg;
	int		len[3];

	len[0] = ft_strlen(prog_name);
	len[1] = ft_strlen(m1);
	len[2] = ft_strlen(m2);
	msg = (char *)malloc(sizeof(char) * len[0] + len[1] + len[2] + 1);
	strcpy(msg, prog_name);
	strcpy(&msg[len[0]], m1);
	strcpy(&msg[len[1] + len[0]], m2);
	ft_putendl_fd(msg, 2);
	free(msg);
}

int	error_ininfile(char *pathname)
{
	if (access(pathname, F_OK) != 0 || access(pathname, R_OK) != 0)
	{
		perror("pipex :");
		return (1);
	}
	return (0);
}

int	error_inoutfile(char *pathname)
{
	if (access(pathname, F_OK) == 0 && access(pathname, W_OK) != 0)
	{
		perror("pipex :");
		return (1);
	}
	return (0);
}
