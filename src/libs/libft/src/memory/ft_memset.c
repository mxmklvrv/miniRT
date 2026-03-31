/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:15:56 by akolupae          #+#    #+#             */
/*   Updated: 2025/04/17 18:57:14 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*char_s;

	if (s == NULL)
		return (NULL);
	char_s = (char *) s;
	i = 0;
	while (i < n)
	{
		char_s[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
