/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:16:54 by akolupae          #+#    #+#             */
/*   Updated: 2025/04/30 16:11:51 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	mem = malloc (nmemb * size);
	if (!mem)
	{
		ft_putendl_fd("Error: malloc", STDERR_FILENO);
		return (NULL);
	}
	ft_bzero(mem, nmemb * size);
	return (mem);
}
