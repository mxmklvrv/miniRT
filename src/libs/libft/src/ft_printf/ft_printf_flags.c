/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:31:47 by akolupae          #+#    #+#             */
/*   Updated: 2025/06/02 14:07:29 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	letter_is_flag(t_flags *flags, const char c);

bool	flags_are_valid(const char *format, int *format_i)
{
	int			i;
	const char	*flags = "#0- +";
	const char	*type = "csiduxXp%";

	i = 0;
	while (format[i] != '\0' && ft_strchr(flags, format[i]) != NULL)
		i++;
	while (format[i] != '\0' && ft_isdigit(format[i]) != 0)
		i++;
	if (format[i] == '.')
		i++;
	while (format[i] != '\0' && ft_isdigit(format[i]) != 0)
		i++;
	if (format[i] != '\0' && ft_strchr(type, format[i]) != NULL)
	{
		*format_i += i + 1;
		return (true);
	}
	return (false);
}

void	fill_flags(t_flags *flags, const char *format)
{
	int	i;

	i = 0;
	*flags = (t_flags){false, false, false, false, false, true, '\0', 0, -1};
	while (format[i] != '\0' && letter_is_flag(flags, format[i]))
		i++;
	if (ft_isdigit(format[i]) != 0)
		flags->width = ft_atoi(&format[i]);
	while (ft_isdigit(format[i]))
		i++;
	if (format[i] == '.')
	{
		i++;
		flags->precision = ft_atoi(&format[i]);
	}
	while (ft_isdigit(format[i]))
		i++;
	flags->type = format[i];
}

static bool	letter_is_flag(t_flags *flags, const char c)
{
	const char	*type = "#0- +";

	if (ft_strchr(type, c) != NULL)
	{
		if (c == '#')
			flags->number = true;
		else if (c == '0')
			flags->zero = true;
		else if (c == '-')
			flags->minus = true;
		else if (c == ' ')
			flags->space = true;
		else if (c == '+')
			flags->plus = true;
		return (true);
	}
	return (false);
}

void	check_flags(t_flags *flags)
{
	if (flags->zero && flags->minus)
		flags->is_valid = false;
	if (flags->space && flags->plus)
		flags->is_valid = false;
	if (flags->number && !(flags->type == 'x' || flags->type == 'X'))
		flags->is_valid = false;
	if (flags->plus && !(flags->type == 'd' || flags->type == 'i'))
		flags->is_valid = false;
	if (flags->space && !(flags->type == 'd' || flags->type == 'i'))
		flags->is_valid = false;
	if (flags->zero && (flags->type == 'c' || flags->type == 's'
			|| flags->type == 'p'))
		flags->is_valid = false;
}
