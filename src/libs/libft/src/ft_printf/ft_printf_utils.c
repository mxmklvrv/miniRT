/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:44:51 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/11 13:12:09 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	putchar_loop(int fd, int c, int n);

int	print_char(int fd, int c, t_flags flags)
{
	int	char_count;
	int	space_count;

	if (!flags.minus)
		space_count = putchar_loop(fd, (int) ' ', flags.width - 1);
	char_count = write(fd, &c, 1);
	if (flags.minus)
		space_count = putchar_loop(fd, (int) ' ', flags.width - 1);
	if (char_count == -1 || space_count == -1)
		return (-1);
	return (char_count + space_count);
}

static int	putchar_loop(int fd, int c, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		if (write(fd, &c, 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

char	*print_ptr(unsigned long ptr)
{
	char	*str;

	if (ptr == 0)
		return (print_null('p'));
	str = ft_itoa_base(ptr, BASE_HEX);
	str = format_number(str, 'p');
	return (str);
}

char	*print_null(char type)
{
	char		*str;
	const char	*null_str = "(null)";
	const char	*nil_str = "(nil)";

	if (type == 'p')
	{
		str = ft_calloc(6, sizeof(char));
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, nil_str, 6);
	}
	else
	{
		str = ft_calloc(7, sizeof(char));
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, null_str, 7);
	}
	return (str);
}
