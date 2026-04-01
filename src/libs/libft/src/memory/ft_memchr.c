/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:51:20 by akolupae          #+#    #+#             */
/*   Updated: 2025/05/30 14:01:14 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*char_s;

	i = 0;
	if (s == NULL)
		return (NULL);
	char_s = (unsigned char *) s;
	while (i < n)
	{
		if (char_s[i] == (unsigned char) c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
