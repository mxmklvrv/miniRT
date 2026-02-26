#include "minirt.h"

void	draw_scene(t_data *data, t_scene *scene)
{
	t_pixel	pixel;
	t_ray	ray;

	setup_scene(scene);
	ray.origin = scene->cam.orient.origin;
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

void	setup_scene(t_scene *scene)
{
	setup_camera_angle(&scene->cam);
	//setup_object_matrix(scene->obj_list);
}

/*
 * Calculates pixel size relative to 3d world depending on camera fov.
 * Distance between camera and 2d screen is assumed to be 1.
 */
void	setup_camera_angle(t_cam *cam)
{
	cam->pixel_size = 1 * tanf(degrees_to_radians(cam->fov / 2)) * 2
		/ ft_max(2, WIDTH, HEIGHT);
	//cam->matrix = ;
	//t_vec3	opposite_cam;
	//const t_vec3	up_view = new_vector(0, 0, 1);

	//cam->orient.direction = vector_normalize(cam->orient.direction);
	//opposite_cam = vector_multiply(cam->orient.direction, -1);
	//cam->vector_i = vector_cross(opposite_cam,up_view);
	//cam->vector_j = vector_cross(opposite_cam, cam->vector_i);
}

void	setup_object_matrix(t_olist *obj_list)
{
	while (obj_list)
	{
		if (obj_list->obj_type == SP)
			set_matrix(&obj_list->matrix, new_scaling_matrix(1, 0.5, 1));
		obj_list = obj_list->next;
	}
}

void	set_matrix(t_matrix *old_m, t_matrix new_m)
{
	free_matrix(*old_m);
	*old_m = new_m;
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
	t_ray	obj_ray;

	color = scene->ambient.colour;
	closest = -1;
	obj_list = scene->obj_list;
	while (obj_list)
	{
		obj_ray = ray; //ray_transform_inverse(ray, obj_list->matrix);
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

