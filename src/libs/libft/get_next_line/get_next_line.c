/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:55:27 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/05 18:53:47 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE * (BUFFER_SIZE > 0) + 1];
	char		*output;
	int			check[1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	output = NULL;
	*check = 0;
	output = check_buffer(buffer, output, check);
	if (*check == 1)
		return (NULL);
	if (output != NULL && output[ft_strlen_modified(output) - 1] == '\n')
		return (output);
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		output = check_buffer(buffer, output, check);
		if (*check == 1)
			return (NULL);
		if (output[ft_strlen_modified(output) - 1] == '\n')
			return (output);
	}
	return (output);
}
