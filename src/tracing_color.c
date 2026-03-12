#include "minirt.h"

static void		find_closest_intersection(t_ray ray, t_shape *shape, t_intersection *closest);

int	trace_color(t_ray ray, t_scene *scene)
{
	t_olist			*obj_list;
	int				color;
	t_intersection	closest;

	closest.count = 0;
	obj_list = scene->obj_list;
	while (obj_list)
	{
		find_closest_intersection(ray, obj_list->shape, &closest);
		obj_list = obj_list->next;
	}
	if (closest.count == 0)
		return (scene->ambient.color);
	//color = closest.shape->color;
	color = lighting(scene->light, scene->ambient, closest, ray);
	return (color);
}

static void	find_closest_intersection(t_ray ray, t_shape *shape, t_intersection *closest)
{
	t_intersection	current;
	float	hit_current;
	float	hit_closest;

	//ray = ray_transform(ray, shape->matrix);
	current = get_intersection(ray, shape);
	if (current.count == 0)
		return ;
	hit_current = get_closest_hit(current);
	hit_closest = get_closest_hit(*closest);
	if (hit_current > 0 && (hit_current < hit_closest || hit_closest < 0))
		*closest = current;
}

float	get_closest_hit(t_intersection intersection)
{
	float	hit;

	if (intersection.count == 0)
		return (-1);
	hit = intersection.val[0];
	if (intersection.count == 2 && intersection.val[1] > 0
		&& (intersection.val[1] < hit || hit < 0))
		hit = intersection.val[1];
	return (hit);
}

