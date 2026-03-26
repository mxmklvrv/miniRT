/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:46:46 by akolupae          #+#    #+#             */
/*   Updated: 2025/04/21 18:59:11 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*s_copy;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	s_copy = ft_calloc(len + 1, sizeof(char));
	if (s_copy == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		s_copy[i] = s[i];
		i++;
	}
	return (s_copy);
}
