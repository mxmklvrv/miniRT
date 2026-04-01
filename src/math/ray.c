/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:08:37 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:08:39 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	new_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	if (!is_point(origin))
		error_msg("Creating ray: origin is not a point", NULL);
	if (is_point(direction))
		error_msg("Creating ray: direction is not a vector", NULL);
	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_vec3	get_ray_point(t_ray ray, float scalar)
{
	return (vector_add(ray.origin, vector_multiply(ray.direction, scalar)));
}
