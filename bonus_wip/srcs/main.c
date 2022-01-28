/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:06:01 by agiraude          #+#    #+#             */
/*   Updated: 2022/01/23 14:31:43 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	file_open(int argc, char **argv, int *file_in, int *file_out)
{
	int	in_err;
	int out_err;

	in_err = error_ininfile(argv[1]);
	out_err = error_inoutfile(argv[argc - 1]);
	if (in_err || out_err)
		return (0);
	*file_in = open(argv[1], O_RDONLY);
	if (*file_in < 0)
	{
		perror(argv[0]);
		return (0);
	}
	*file_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*file_out < 0)
	{
		perror(argv[0]);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int	file_in;
	int	file_out;
	t_cmd	**cmd;

	if (argc != 5)
	{
		errno = EINVAL;
		perror(argv[0]);
		return (1);
	}
	if (!file_open(argc, argv, &file_in, &file_out))
	{
		return (0);
	}
	cmd = cmd_set_all(argc, argv, envp);
	return(pipex(file_in, file_out, cmd));
}
