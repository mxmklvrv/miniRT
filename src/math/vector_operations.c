/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:10:43 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:10:44 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vector_negate(t_vec3 v)
{
	return (new_vector(-v.x, -v.y, -v.z));
}

t_vec3	vector_add(t_vec3 v1, t_vec3 v2)
{
	if (is_point(v1) && is_point(v2))
		error_msg("Adding two points", NULL);
	if (is_point(v1) || is_point(v2))
		return (new_point(
				v1.x + v2.x,
				v1.y + v2.y,
				v1.z + v2.z
			));
	return (new_vector(
			v1.x + v2.x,
			v1.y + v2.y,
			v1.z + v2.z
		));
}

t_vec3	vector_substract(t_vec3 v1, t_vec3 v2)
{
	if (!is_point(v1) && is_point(v2))
		error_msg("Substracting point from vector", NULL);
	if (is_point(v1) != is_point(v2))
		return (new_point(
				v1.x - v2.x,
				v1.y - v2.y,
				v1.z - v2.z
			));
	return (new_vector(
			v1.x - v2.x,
			v1.y - v2.y,
			v1.z - v2.z
		));
}

t_vec3	vector_multiply(t_vec3 v, float scalar)
{
	if (is_point(v))
		error_msg("Multiplying a point", NULL);
	return (new_vector(
			v.x * scalar,
			v.y * scalar,
			v.z * scalar
		));
}

t_vec3	vector_divide(t_vec3 v, float scalar)
{
	if (is_point(v))
		error_msg("Dividing a point", NULL);
	if (scalar == 0)
	{
		error_msg("Dividing by zero", NULL);
		return (v);
	}
	return (new_vector(
			v.x / scalar,
			v.y / scalar,
			v.z / scalar
		));
}
