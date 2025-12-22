/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamzer <rmamzer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:56:08 by rmamzer           #+#    #+#             */
/*   Updated: 2025/07/05 18:54:03 by rmamzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*update_output(char *buffer, char *output, int	*check)
{
	size_t	buf_len;
	size_t	out_len;
	char	*new_output;

	buf_len = ft_strlen_modified(buffer);
	out_len = ft_strlen_modified(output);
	new_output = malloc(buf_len + out_len + 1);
	if (!new_output)
	{
		free(output);
		output = NULL;
		*check = 1;
		return (NULL);
	}
	ft_strcpy_modified(new_output, output, out_len);
	ft_strcpy_modified(&new_output[out_len], buffer, buf_len);
	free(output);
	return (new_output);
}

void	ft_strcpy_modified(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		src[i] = '\0';
		i++;
	}
	dest[i] = '\0';
}

char	*check_buffer(char *buffer, char *output, int	*check)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buffer[i] != '\0')
			return (update_output(&buffer[i], output, check));
		i++;
	}
	return (output);
}

size_t	ft_strlen_modified(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	{
		while (str[i] != '\0' && str[i] != '\n')
			i++;
	}
	if (str[i] == '\n')
		i++;
	return (i);
}
