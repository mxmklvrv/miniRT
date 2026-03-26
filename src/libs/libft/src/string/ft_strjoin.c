/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:02:18 by akolupae          #+#    #+#             */
/*   Updated: 2025/04/22 12:11:16 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*s_join;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s_join = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (s_join == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	ft_strlcpy(s_join, s1, len1 + 1);
	ft_strlcat(s_join, s2, len1 + len2 + 1);
	return (s_join);
}
