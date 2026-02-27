#include "minirt.h"

static bool	is_closest(t_intersection intersection, int *closest);

/*
 * Returns normalized vector from camera origin to point in 3d coordinates
 */
t_vec3	get_direction_for_position(t_pixel pixel, t_cam cam)
{
	t_vec3		direction;
	t_matrix	rotation;
	float		multiplier;


	multiplier = degrees_to_radians(cam.fov) / ft_max(2, WIDTH, HEIGHT);
	rotation = new_rotation_y_matrix((pixel.i - WIDTH / 2) * multiplier);
	direction = matrix_multiply_by_vector(rotation, cam.orient.direction);
	free_matrix(rotation);
	rotation = new_rotation_x_matrix((pixel.j - HEIGHT / 2) * multiplier);
	direction = matrix_multiply_by_vector(rotation, direction);
	free_matrix(rotation);
	direction = vector_normalize(direction);
	return (direction);
}

int	trace_color(t_ray ray, t_scene *scene)
{
	t_olist	*obj_list;
	int		color;
	t_intersection	intersection;
	int		closest;
	t_ray	obj_ray;

	color = scene->ambient.colour;
	closest = -1;
	obj_list = scene->obj_list;
	while (obj_list)
	{
		obj_ray = ray_transform_inverse(ray, obj_list->matrix);//ray;
		if (obj_list->obj_type == SP)
		{
			intersection = hit_sp(obj_ray, (t_sp *)obj_list->obj);
			if (is_closest(intersection, &closest))
				color = obj_list->colour;
		}
		else if (obj_list->obj_type == CY)
		{
			intersection = hit_cy(obj_ray, (t_cy *)obj_list->obj);
			if (is_closest(intersection, &closest))
				color = obj_list->colour;
		}
		else if (obj_list->obj_type == PL)
		{
			intersection = hit_pl(obj_ray, (t_pl *)obj_list->obj);
			if (is_closest(intersection, &closest))
				color = obj_list->colour;
		}
		else
			continue ;
		obj_list = obj_list->next;
	}
	return (color);
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

