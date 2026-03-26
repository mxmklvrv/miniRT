/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:19:50 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/11 13:09:28 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_content(int fd, const char *format, va_list args, int *i);
static char	*get_str(t_flags flags, va_list args);
static char	*format_str(char *str, t_flags flags);

int	ft_printf(int fd, const char *format, ...)
{
	int		print_count;
	int		result;
	va_list	args;
	int		i;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	print_count = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			result = print_content(fd, &format[i + 1], args, &i);
		else
			result = ft_putchar_fd(format[i], 1);
		if (result == -1)
			return (-1);
		print_count += result;
		i++;
	}
	va_end(args);
	return (print_count);
}

static int	print_content(int fd, const char *format, va_list args, int *i)
{
	int		print_count;
	t_flags	flags;
	char	*str;

	if (!flags_are_valid(format, i))
		return (-1);
	fill_flags(&flags, format);
	if (flags.type == '%')
		return (write(1, "%", 1));
	check_flags(&flags);
	if (flags.type == 'c')
		return (print_char(fd, va_arg(args, int), flags));
	str = get_str(flags, args);
	if (str == NULL)
		str = print_null(flags.type);
	str = format_str(str, flags);
	print_count = ft_putstr_fd(str, fd);
	free(str);
	str = NULL;
	if (!flags.is_valid)
		return (-1);
	return (print_count);
}

static char	*get_str(t_flags flags, va_list args)
{
	if (flags.type == 's')
		return (ft_strdup(va_arg(args, const char *)));
	else if (flags.type == 'i' || flags.type == 'd')
		return (ft_itoa(va_arg(args, int)));
	else if (flags.type == 'u')
		return (ft_itoa_base(va_arg(args, unsigned int), BASE_DEC));
	else if (flags.type == 'x')
		return (ft_itoa_base(va_arg(args, unsigned int), BASE_HEX));
	else if (flags.type == 'X')
		return (ft_itoa_base(va_arg(args, unsigned int), BASE_HEX_UPCASE));
	else if (flags.type == 'p')
		return (print_ptr(va_arg(args, unsigned long)));
	return (NULL);
}

static char	*format_str(char *str, t_flags flags)
{
	if (flags.precision > -1 && flags.is_valid)
		str = format_precision(str, flags.precision, flags.type);
	if (flags.number && flags.is_valid && str[0] != '0')
		str = format_number(str, flags.type);
	if ((flags.space || flags.plus) && flags.is_valid)
		str = format_space_plus(str, flags.plus);
	if (flags.width > (int) ft_strlen(str))
	{
		str = format_width(str, flags.width, flags.minus);
		if (flags.zero && flags.is_valid && flags.precision == -1)
			str = format_zero(str, flags.space);
	}
	return (str);
}
