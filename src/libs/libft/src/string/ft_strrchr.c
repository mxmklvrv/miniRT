/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:46:29 by akolupae          #+#    #+#             */
/*   Updated: 2025/04/19 17:06:44 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last;

	if (s == NULL)
		return (NULL);
	i = 0;
	last = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			last = i;
		i++;
	}
	if (s[i] == (char) c)
		last = i;
	if (last >= 0)
		return ((char *)&s[last]);
	return (NULL);
}
