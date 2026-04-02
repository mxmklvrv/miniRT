/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:10:33 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:10:34 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	new_vector(float x, float y, float z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = 0;
	return (res);
}

t_vec3	new_point(float x, float y, float z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = 1;
	return (res);
}

bool	is_point(t_vec3 v)
{
	return (v.w == 1);
}

bool	vector_is_zero(t_vec3 v)
{
	if (is_point(v))
		return (false);
	if (v.x == 0 && v.y == 0 && v.z == 0)
		return (true);
	return (false);
}
