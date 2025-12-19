/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:10:21 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/24 16:40:51 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ftpf_putchar(char c)
{
	return (write (1, &c, 1));
}

int	ftpf_putstr(char *str)
{
	int	written;
	int	totalwritten;

	if (!str)
		return (write(1, "(null)", 6));
	written = 0;
	totalwritten = 0;
	while (*str)
	{
		written = write(1, str, 1);
		if (written == -1)
			return (-1);
		totalwritten++;
		str++;
	}
	return (totalwritten);
}

int	ftpf_putbase(unsigned long num, unsigned int base, char *str)
{
	int	total;
	int	written;

	total = 0;
	written = 0;
	if (num > base - 1)
		total = ftpf_putbase(num / base, base, str);
	if (total == -1)
		return (-1);
	written = write(1, &str[num % base], 1);
	if (written == -1)
		return (-1);
	total += written;
	return (total);
}

int	ftpf_putint(long num)
{
	int	printsign;
	int	printnum;

	printsign = 0;
	printnum = 0;
	if (num < 0)
	{
		printsign = write(1, "-", 1);
		num = -num;
	}
	printnum = ftpf_putbase(num, 10, BASE10);
	if (printnum == -1 || printsign == -1)
		return (-1);
	return (printsign + printnum);
}

int	ftpf_putptr( void *ptr)
{
	int	preffix;
	int	printaddress;

	if (!ptr)
		return (ftpf_putstr("(nil)"));
	preffix = 0;
	printaddress = 0;
	preffix = write(1, "0x", 2);
	printaddress = ftpf_putbase((unsigned long)ptr, 16, BASE16L);
	if (preffix == -1 || printaddress == -1)
		return (-1);
	return (preffix + printaddress);
}
