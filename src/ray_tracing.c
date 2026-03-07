#include "minirt.h"

static bool	intersection_is_closest(t_ray ray, t_shape *shape, int *closest);
static bool	is_closest(t_intersection intersection, int *closest);

int	trace_color(t_ray ray, t_scene *scene)
{
	t_olist	*obj_list;
	int		color;
	int		closest;

	color = scene->ambient.colour;
	closest = -1;
	obj_list = scene->obj_list;
	while (obj_list)
	{
		if (intersection_is_closest(ray, obj_list->shape, &closest))
			color = obj_list->shape->colour;
		obj_list = obj_list->next;
	}
	return (color);
}

static bool	intersection_is_closest(t_ray ray, t_shape *shape, int *closest)
{
	t_intersection	intersection;

	//ray = ray_transform(ray, shape->matrix);
	if (shape->obj_type == SP)
		intersection = hit_sp(ray, shape);
	else if (shape->obj_type == CY)
		intersection = hit_cy(ray, shape);
	else if (shape->obj_type == PL)
		intersection = hit_pl(ray, shape);
	else
		intersection.count = 0;
	if (is_closest(intersection, closest))
		return (true);
	return (false);
}

static bool	is_closest(t_intersection intersection, int *closest)
{
	float	hit;

	if (intersection.count == 0)
		return (false);
	hit = intersection.val[0];
	if (intersection.count == 2 && intersection.val[1] > 0
		&& (intersection.val[1] < hit || hit < 0))
		hit = intersection.val[1];
	if (hit > 0 && (hit < *closest || *closest < 0))
	{
		*closest = hit;
		return (true);
	}
	return (false);
}

