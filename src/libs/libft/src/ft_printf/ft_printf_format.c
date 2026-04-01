/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:14:35 by akolupae          #+#    #+#             */
/*   Updated: 2025/05/30 15:26:48 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*format_zero(char *str, bool space)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	if (ft_strchr(str, '-') != NULL || ft_strchr(str, '+') != NULL || space)
	{
		if (ft_strchr(str, '-') != NULL)
			str[0] = '-';
		else if (ft_strchr(str, '+') != NULL)
			str[0] = '+';
		i = 1;
	}
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '-' || str[i] == '+')
			str[i] = '0';
		i++;
	}
	return (str);
}

char	*format_number(char *str, char type)
{
	char	*new_str;

	if (type == 'X')
		new_str = ft_strjoin("0X", str);
	else
		new_str = ft_strjoin("0x", str);
	free(str);
	str = NULL;
	return (new_str);
}

char	*format_space_plus(char *str, bool plus)
{
	char	*new_str;
	int		len;

	if (str == NULL)
		return (NULL);
	if (str[0] == '-')
		return (str);
	len = ft_strlen(str);
	new_str = ft_calloc(len + 2, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[0] = ' ';
	if (plus)
		new_str[0] = '+';
	ft_strlcpy(&new_str[1], (const char *) str, len + 1);
	free(str);
	str = NULL;
	return (new_str);
}

char	*format_width(char *str, int width, bool minus)
{
	char	*new_str;
	int		len;

	new_str = ft_calloc(width + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_memset(new_str, (int) ' ', width);
	len = ft_strlen(str);
	if (minus)
		ft_memcpy(&new_str[0], (const char *) str, len);
	else
		ft_memcpy(&new_str[width - len], (const char *) str, len);
	free(str);
	str = NULL;
	return (new_str);
}
