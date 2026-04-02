/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_is_inside.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:10:05 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:10:06 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	is_inside_pl(t_vec3 point, t_shape *sp);
static bool	is_inside_sp(t_vec3 point, t_shape *sp);
static bool	is_inside_cy(t_vec3 point, t_shape *cy);

bool	is_inside(t_vec3 point, t_shape *shape)
{
	if (shape->obj_type == SP)
		return (is_inside_sp(point, shape));
	if (shape->obj_type == PL)
		return (is_inside_pl(point, shape));
	if (shape->obj_type == CY)
		return (is_inside_cy(point, shape));
	return (false);
}

static bool	is_inside_pl(t_vec3 point, t_shape *pl)
{
	t_vec3	pl_to_point;

	pl_to_point = vector_substract(point, pl->normal.origin);
	if (vector_dot(pl_to_point, pl->normal.direction) < 0)
		return (true);
	return (false);
}

static bool	is_inside_sp(t_vec3 point, t_shape *sp)
{
	t_vec3	sp_to_point;

	sp_to_point = vector_substract(point, sp->center);
	if (vector_magnitude(sp_to_point) < sp->radius)
		return (true);
	return (false);
}

static bool	is_inside_cy(t_vec3 point, t_shape *cy)
{
	t_vec3	cy_to_point;
	float	axis_proj;
	t_vec3	point_on_axis;
	float	normal_proj;

	cy_to_point = vector_substract(point, cy->normal.origin);
	axis_proj = vector_dot(cy_to_point, cy->normal.direction);
	point_on_axis = vector_add(cy->normal.origin,
			vector_multiply(cy->normal.direction, axis_proj));
	vector_normalize(vector_substract(point, point_on_axis));
	normal_proj = vector_dot(cy_to_point,
			vector_normalize(vector_substract(point, point_on_axis)));
	if (fabsf(axis_proj) < cy->half_height
		&& fabsf(normal_proj) < cy->radius)
		return (true);
	return (false);
}
