/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:00:12 by akolupae          #+#    #+#             */
/*   Updated: 2025/05/01 14:31:54 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	sub_len;
	char			*sub_s;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	sub_len = 0;
	while (s[sub_len + start] != '\0' && (size_t) sub_len < len)
		sub_len++;
	sub_s = ft_calloc(sub_len + 1, sizeof(char));
	if (sub_s == NULL)
		return (NULL);
	i = 0;
	while (i < sub_len)
	{
		sub_s[i] = s[start + i];
		i++;
	}
	return (sub_s);
}
