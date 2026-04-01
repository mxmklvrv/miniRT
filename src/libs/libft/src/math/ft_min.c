/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:04:19 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:04:21 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns minimum value from given.
 *
 * @param	int		arg_count number of expected values.
 * @param	int		... values.
 * @returns	int		max value from given or 0.
 */
int	ft_min(int arg_count, ...)
{
	va_list	arg_ptr;
	int		i;
	int		current;
	int		min;

	va_start(arg_ptr, arg_count);
	i = 0;
	min = 0;
	while (i < arg_count)
	{
		current = va_arg(arg_ptr, int);
		if (i == 0 || current < min)
			min = current;
		i++;
	}
	va_end(arg_ptr);
	return (min);
}
