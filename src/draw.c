#include "minirt.h"

void	setup_camera_angle(t_cam *cam);
t_vec3	get_direction_for_position(t_pixel pixel, t_cam cam);
int		trace_color(t_ray ray, t_scene *scene);
bool	is_closest(t_intersection intersection, int *closest);

void	draw_scene(t_data *data, t_scene *scene)
{
	t_pixel	pixel;
	t_ray	ray;

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

/*
 * Calculate angle (in radians, counter-clockwise) between screen projection
 * and 0x axis on xy plane. This angle is equal to angle between camera normal
 * and 0y axis. If angle is zero screen is parallel to 0x axis and camera
 * normal is parallel to 0y axis.
 * Returns sine and cosine of this angle in form of t_vec3.
 */
//void	setup_camera_angle(t_cam *cam)
//{
//	t_vec3	opposite_cam;
//	const t_vec3	up_view = {0, 0, 1, 0};

//	cam->orient.direction = vector_normalize(cam->orient.direction);
//	opposite_cam = vector_multiply(cam->orient.direction, -1);
//	cam->vector_i = vector_cross(opposite_cam,up_view);
//	cam->vector_j = vector_cross(opposite_cam, cam->vector_i);
//}

/*
 * Returns normalized vector from camera origin to point in 3d coordinates
 */
t_vec3	get_direction_for_position(t_pixel pixel, t_cam cam)
{
	t_vec3	direction;
	t_vec3	position_width;
	t_vec3	position_heigth;

	position_width = vector_multiply(cam.vector_i, pixel.i - WIDTH / 2);
	position_heigth = vector_multiply(cam.vector_j, pixel.j - HEIGHT / 2);
	direction = vector_add(position_width, position_heigth);
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

