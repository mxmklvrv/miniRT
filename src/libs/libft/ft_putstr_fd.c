/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:32:44 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/25 13:22:52 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Outputs the string ’s’ to the specified file
// descriptor.
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (*s)
	{
		i = ft_strlen(s);
		write (fd, s, i);
	}
}
