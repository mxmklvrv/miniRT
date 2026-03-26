/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:52:52 by akolupae          #+#    #+#             */
/*   Updated: 2025/05/30 15:22:04 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(unsigned long n, char *base);
static void	fill_str(char *str_end, unsigned long n, char *base);

char	*ft_itoa_base(unsigned long n, char *base)
{
	int		digits;
	char	*str;

	if (n == 0)
		digits = 1;
	else
		digits = count_digits(n, base);
	str = ft_calloc(digits + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	fill_str(&str[digits - 1], n, base);
	return (str);
}

static int	count_digits(unsigned long n, char *base)
{
	int				digits;
	unsigned int	len;

	digits = 0;
	len = ft_strlen(base);
	while (n >= 1)
	{
		digits++;
		n = n / len;
	}
	return (digits);
}

static void	fill_str(char *str_end, unsigned long n, char *base)
{
	unsigned int	len;

	len = ft_strlen(base);
	if (n > (len - 1))
		fill_str(str_end - 1, n / len, base);
	*str_end = base[n % len];
}
