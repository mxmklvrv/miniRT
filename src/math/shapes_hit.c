/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:09:37 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:09:40 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	hit_sp(t_ray ray, t_shape *sp, t_hit *hit);
static void	hit_pl(t_ray ray, t_shape *pl, t_hit *hit);

t_hit	get_hit(t_ray ray, t_shape *shape)
{
	t_hit	hit;

	hit.count = 0;
	if (shape->obj_type == SP)
		hit_sp(ray, shape, &hit);
	else if (shape->obj_type == CY)
		hit_cy(ray, shape, &hit);
	else if (shape->obj_type == PL)
		hit_pl(ray, shape, &hit);
	return (hit);
}

static void	hit_sp(t_ray ray, t_shape *sp, t_hit *hit)
{
	t_quad	quad;

	hit->shape = sp;
	quad.vec_to_obj = vector_substract(ray.origin, sp->center);
	quad.a = vector_dot(ray.direction, ray.direction);
	quad.b = 2 * vector_dot(ray.direction, quad.vec_to_obj);
	quad.c = vector_dot(quad.vec_to_obj, quad.vec_to_obj)
		- sp->radius * sp->radius;
	solve_quadratic_equasion(quad, hit);
}

static void	hit_pl(t_ray ray, t_shape *pl, t_hit *hit)
{
	float	denominator;
	t_vec3	vec_to_obj;

	hit->shape = pl;
	denominator = vector_dot(ray.direction, pl->normal.direction);
	if (fabsf(denominator) < EPSILON)
		return ;
	hit->count = 1;
	vec_to_obj = vector_substract(pl->normal.origin, ray.origin);
	hit->val[0] = vector_dot(vec_to_obj, pl->normal.direction)
		/ denominator;
}
