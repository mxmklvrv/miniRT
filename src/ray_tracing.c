#include "minirt.h"

static void		find_closest_intersection(t_ray ray, t_shape *shape, t_intersection *closest);
static float	get_closest_hit(t_intersection intersection);

int	lighting(t_light light, t_intersection intersection, t_ray ray);

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
	color = scene->ambient.color;
	if (closest.count > 0)
	{
		color = closest.shape->color;
		//color = lighting(scene->light, closest, ray);
	}
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

static float	get_closest_hit(t_intersection intersection)
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

//int	lighting(t_light light, t_intersection intersection, t_ray ray)
//{
//	int	color;
//	float	ambient;
//	float	diffuse;
//	float	specular;
//	t_vec3	point;

//	color = color_mix(intersection.shape->color, color_multiply(light.color, light.bright));
//	point = get_ray_point(ray, get_closest_hit(intersection));
//	ambient = 0.1;
//	diffuse = 0.9 * cosf(get_normal(intersection.shape, point), light.pos);
//	specular = 0.9 * ;
//	color = color_multiply(intersection.shape->color, ambient + diffuse + specular);
//	return (color);
//}



