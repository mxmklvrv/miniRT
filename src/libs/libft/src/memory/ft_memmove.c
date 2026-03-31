/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:40:37 by akolupae          #+#    #+#             */
/*   Updated: 2025/04/18 15:08:26 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reverse(char *dest, char *src, size_t i);
static void	forvard(char *dest, char *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*char_dest;
	char	*char_src;

	if (src == NULL || dest == NULL)
		return (NULL);
	if (n > 0)
	{
		char_dest = (char *) dest;
		char_src = (char *) src;
		if (src < dest)
			reverse(char_dest, char_src, n);
		else
			forvard(char_dest, char_src, n);
	}
	return (dest);
}

static void	reverse(char *dest, char *src, size_t i)
{
	while (i > 0)
	{
		i--;
		dest[i] = src[i];
	}
}

static void	forvard(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}
