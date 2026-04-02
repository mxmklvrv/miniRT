/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_hit_cy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:09:49 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:09:52 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	hit_cy_caps(t_ray ray, t_shape *cy, t_hit *hit);
static void	check_cap_hit(t_ray ray, t_ray normal, float *hit, float radius);

void	hit_cy(t_ray ray, t_shape *cy, t_hit *hit)
{
	t_quad	quad;
	t_vec3	ray_perp;
	t_vec3	obj_perp;

	hit->shape = cy;
	quad.vec_to_obj = vector_substract(ray.origin, cy->normal.origin);
	quad.ray_proj = vector_dot(ray.direction, cy->normal.direction);
	quad.obj_proj = vector_dot(quad.vec_to_obj, cy->normal.direction);
	ray_perp = vector_substract(ray.direction,
			vector_multiply(cy->normal.direction, quad.ray_proj));
	obj_perp = vector_substract(quad.vec_to_obj,
			vector_multiply(cy->normal.direction, quad.obj_proj));
	quad.a = vector_dot(ray_perp, ray_perp);
	quad.b = 2 * (vector_dot(ray_perp, obj_perp));
	quad.c = vector_dot(obj_perp, obj_perp) - cy->radius * cy->radius;
	solve_quadratic_equasion(quad, hit);
	if (hit->count == 0)
		return ;
	if (fabsf(quad.ray_proj * hit->val[0] + quad.obj_proj) > cy->half_height)
		hit->val[0] = -1;
	if (fabsf(quad.ray_proj * hit->val[1] + quad.obj_proj) > cy->half_height)
		hit->val[1] = -1;
	if (fabsf(quad.ray_proj) < EPSILON)
		return ;
	hit_cy_caps(ray, cy, hit);
}

static void	hit_cy_caps(t_ray ray, t_shape *cy, t_hit *hit)
{
	t_ray	normal;

	hit->count = 4;
	normal.origin = vector_add(cy->normal.origin,
			vector_multiply(cy->normal.direction, cy->half_height));
	normal.direction = cy->normal.direction;
	check_cap_hit(ray, normal, &hit->val[2], cy->radius);
	normal.origin = vector_substract(cy->normal.origin,
			vector_multiply(cy->normal.direction, cy->half_height));
	normal.direction = vector_negate(cy->normal.direction);
	check_cap_hit(ray, normal, &hit->val[3], cy->radius);
}

static void	check_cap_hit(t_ray ray, t_ray normal, float *hit, float radius)
{
	t_vec3	vec_to_obj;
	float	ray_proj;
	t_vec3	center_to_hit;

	vec_to_obj = vector_substract(normal.origin, ray.origin);
	ray_proj = vector_dot(ray.direction, normal.direction);
	*hit = vector_dot(vec_to_obj, normal.direction) / ray_proj;
	center_to_hit = vector_substract(get_ray_point(ray, *hit), normal.origin);
	if (vector_magnitude(center_to_hit) > radius)
		*hit = -1;
}
