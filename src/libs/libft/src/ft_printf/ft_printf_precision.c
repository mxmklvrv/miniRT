/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:14:35 by akolupae          #+#    #+#             */
/*   Updated: 2025/06/01 18:18:22 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*format_precision_s(char *str, int precision, int len);
static char	*format_precision_num(char *str, int precision, int len);

char	*format_precision(char *str, int precision, char type)
{
	char	*new_str;
	int		len;

	len = ft_strlen(str);
	if (type == 's' || (type != 's' && precision == 0))
		new_str = format_precision_s(str, precision, len);
	else
		new_str = format_precision_num(str, precision, len);
	return (new_str);
}

static char	*format_precision_s(char *str, int precision, int len)
{
	char	*new_str;

	if (precision >= len)
		return (str);
	new_str = ft_calloc(precision + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, (const char *) str, precision + 1);
	free(str);
	str = NULL;
	return (new_str);
}

static char	*format_precision_num(char *str, int precision, int len)
{
	char	*new_str;
	int		i;

	i = 0;
	if (precision < len || (precision == len && str[0] != '-'))
		return (str);
	if (str[0] == '-')
		i = 1;
	new_str = ft_calloc(precision + i + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str = ft_memset((void *) new_str, '0', precision + i);
	if (str[0] == '-')
		new_str[0] = '-';
	ft_strlcpy(&new_str[i + precision - len + i], &str[i], len - i + 1);
	free(str);
	str = NULL;
	return (new_str);
}
