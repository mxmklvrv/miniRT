/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:07:55 by akolupae          #+#    #+#             */
/*   Updated: 2025/05/30 13:50:02 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long int	ln;
	int			result;

	ln = n;
	result = 0;
	if (ln < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		result = 1;
		ln = -ln;
	}
	if (ln > 9)
		result += ft_max(ft_putnbr_fd(ln / 10, fd), -1);
	if (ft_putchar_fd(ln % 10 + '0', fd) == -1 || result == -1)
		return (-1);
	return (result + 1);
}
