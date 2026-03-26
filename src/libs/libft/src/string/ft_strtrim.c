/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:50:23 by akolupae          #+#    #+#             */
/*   Updated: 2025/04/24 21:56:38 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	check_set(char c, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*s_trim;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (check_set(s1[start], set) && start < end)
		start++;
	while (check_set(s1[end - 1], set) && end > start)
		end--;
	s_trim = (char *) malloc ((end - start + 1) * sizeof(char));
	if (s_trim == NULL)
		return (NULL);
	ft_strlcpy(s_trim, &s1[start], end - start + 1);
	return (s_trim);
}

static bool	check_set(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (true);
		i++;
	}
	return (false);
}
