/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:43:18 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:43:19 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	trace_color(t_ray ray, t_scene *scene)
{
	t_olist	*obj_list;
	int		color;
	t_hit	closest;

	closest.count = 0;
	obj_list = scene->obj_list;
	while (obj_list)
	{
		find_closest_hit(ray, obj_list->shape, &closest);
		obj_list = obj_list->next;
	}
	if (closest.count == 0)
		return (BACKGROUNG);
	color = lighting(scene, closest, ray);
	return (color);
}

void	find_closest_hit(t_ray ray, t_shape *shape, t_hit *closest)
{
	t_hit	current;
	float	hit_current;
	float	hit_closest;

	current = get_hit(ray, shape);
	if (current.count == 0)
		return ;
	hit_current = get_closest_hit(current);
	hit_closest = get_closest_hit(*closest);
	if (hit_current > 0 && (hit_current < hit_closest || hit_closest < 0))
		*closest = current;
}

float	get_closest_hit(t_hit hit)
{
	float	min;
	int		i;

	if (hit.count == 0)
		return (-1);
	min = hit.val[0];
	i = 1;
	while (i < hit.count)
	{
		if (hit.val[i] > 0 && (hit.val[i] < min || min < 0))
			min = hit.val[i];
		i++;
	}
	return (min);
}
