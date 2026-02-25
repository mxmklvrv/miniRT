#include "minirt.h"

void	draw_scene(t_data *data, t_scene *scene)
{
	t_pixel	pixel;
	t_ray	ray;

	ray.origin = scene->cam.orient.origin;
	setup_camera_angle(&scene->cam);
	pixel.j = 0;
	while (pixel.j < HEIGHT)//TODO: add multi threading
	{
		pixel.i = 0;
		while (pixel.i < WIDTH)
		{
			ray.direction = get_direction_for_position(pixel, scene->cam);
			pixel.color = trace_color(ray, scene);
			ft_mlx_put_pixel(data, pixel);//TODO: add writting to ppm(?)
			pixel.i++;
		}
		pixel.j++;
	}
	printf("Finished\n");
}

/*
 * Calculates pixel size relative to 3d world depending on camera fov.
 * Distance between camera and 2d screen is assumed to be 1.
 */
void	setup_camera_angle(t_cam *cam)
{
	cam->pixel_size = 1 * tanf(degrees_to_radians(cam->fov / 2)) * 2
		/ ft_max(2, WIDTH, HEIGHT);
	//t_vec3	opposite_cam;
	//const t_vec3	up_view = new_vector(0, 0, 1);

	//cam->orient.direction = vector_normalize(cam->orient.direction);
	//opposite_cam = vector_multiply(cam->orient.direction, -1);
	//cam->vector_i = vector_cross(opposite_cam,up_view);
	//cam->vector_j = vector_cross(opposite_cam, cam->vector_i);
}

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

	color = scene->ambient.colour;
	closest = -1;
	obj_list = scene->obj_list;
	while (obj_list)
	{
		if (obj_list->obj_type == SP)
		{
			intersection = hit_sp(ray, (t_sp *)obj_list->obj);
			if (is_closest(intersection, &closest))
				color = obj_list->colour;
		}
		else if (obj_list->obj_type == CY)
		{
			intersection = hit_cy(ray, (t_cy *)obj_list->obj);
			if (is_closest(intersection, &closest))
				color = obj_list->colour;
		}
		else if (obj_list->obj_type == PL)
		{
			intersection = hit_pl(ray, (t_pl *)obj_list->obj);
			if (is_closest(intersection, &closest))
				color = obj_list->colour;
		}
		else
			continue ;
		obj_list = obj_list->next;
	}
	return (color);
}

bool	is_closest(t_intersection intersection, int *closest)
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

