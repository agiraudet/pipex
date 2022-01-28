/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 00:47:52 by agiraude          #+#    #+#             */
/*   Updated: 2022/01/23 00:51:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	printf("%s\n", strerror(atoi(argv[1])));
	return (0);
}
