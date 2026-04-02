/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:10:19 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:10:21 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	normal_at_sp(t_vec3 point, t_shape *sp);
static t_vec3	normal_at_cy(t_vec3 point, t_shape *cy);

t_vec3	get_normal(t_shape *shape, t_vec3 point)
{
	if (shape->obj_type == SP)
		return (normal_at_sp(point, shape));
	if (shape->obj_type == PL)
		return (shape->normal.direction);
	if (shape->obj_type == CY)
		return (normal_at_cy(point, shape));
	else
		return (new_vector(0, 1, 0));
}

static t_vec3	normal_at_sp(t_vec3 point, t_shape *sp)
{
	return (vector_normalize(vector_substract(point, sp->center)));
}

static t_vec3	normal_at_cy(t_vec3 point, t_shape *cy)
{
	t_vec3	half_axis;
	t_vec3	cap_center;
	float	axis_proj;
	t_vec3	point_on_axis;

	half_axis = vector_multiply(cy->normal.direction, cy->half_height);
	cap_center = vector_add(cy->normal.origin, half_axis);
	if (vector_magnitude(vector_substract(point, cap_center))
		< cy->radius)
		return (cy->normal.direction);
	cap_center = vector_substract(cy->normal.origin, half_axis);
	if (vector_magnitude(vector_substract(point, cap_center))
		< cy->radius)
		return (vector_negate(cy->normal.direction));
	axis_proj = vector_dot(vector_substract(point, cy->normal.origin),
			cy->normal.direction);
	point_on_axis = vector_add(cy->normal.origin,
			vector_multiply(cy->normal.direction, axis_proj));
	return (vector_normalize(vector_substract(point, point_on_axis)));
}
