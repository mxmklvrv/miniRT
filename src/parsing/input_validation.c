/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:51:26 by mklevero          #+#    #+#             */
/*   Updated: 2026/04/02 16:53:34 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_file_extension(char *file);

int	confirm_input(int ac, char **av)
{
	if (ac != 2)
		return (error_return(ERR_AC, NULL));
	if (rt_file_extension(av[1]) == 1)
		return (error_return(ERR_EXT, av[1]));
	return (0);
}

static int	rt_file_extension(char *file)
{
	size_t	len;

	if (!file)
		return (1);
	len = ft_strlen(file);
	if (len < 3)
		return (1);
	if (ft_strncmp(file + len - 3, ".rt", 3) != 0)
		return (1);
	return (0);
}
