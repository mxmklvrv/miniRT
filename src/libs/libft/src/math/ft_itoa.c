/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:52:52 by akolupae          #+#    #+#             */
/*   Updated: 2025/04/25 13:20:21 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long int n);
static void	fill_str(char *str_end, long int n);

char	*ft_itoa(int n)
{
	long int	ln;
	int			sign;
	int			digits;
	char		*str;

	ln = n;
	sign = 0;
	if (ln < 0)
	{
		sign = 1;
		ln = -ln;
	}
	if (n == 0)
		digits = 1;
	else
		digits = count_digits(ln);
	str = ft_calloc (digits + sign + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	if (sign == 1)
		str[0] = '-';
	fill_str(&str[digits + sign - 1], ln);
	return (str);
}

static int	count_digits(long int n)
{
	int	digits;

	digits = 0;
	while (n >= 1)
	{
		digits++;
		n = n / 10;
	}
	return (digits);
}

static void	fill_str(char *str_end, long int n)
{
	if (n > 9)
		fill_str(str_end - 1, n / 10);
	*str_end = n % 10 + '0';
}
