/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:29:04 by akolupae          #+#    #+#             */
/*   Updated: 2025/04/17 19:15:10 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*char_s;

	if (s == NULL)
		return ;
	char_s = (char *) s;
	i = 0;
	while (i < n)
	{
		char_s[i] = '\0';
		i++;
	}
	return ;
}
