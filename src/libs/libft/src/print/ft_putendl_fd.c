/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:04:35 by akolupae          #+#    #+#             */
/*   Updated: 2025/04/24 17:06:38 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	result;

	result = ft_putstr_fd(s, fd);
	if (result != -1 && write(fd, "\n", 1) != -1)
		return (result + 1);
	return (-1);
}
