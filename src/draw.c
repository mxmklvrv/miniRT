#include "minirt.h"

//TODO: Check if ray or cam is inside any obj
void	setup_camera_angle(t_cam *cam);
t_ray	get_ray_for_position(t_pixel pixel, t_cam cam);

//void	normalize_pos(t_scene *scene);
int		trace_color(t_ray ray, t_scene *scene);
bool	is_closest(int distance, int closest);

void	draw_scene(t_data *data, t_scene *scene)
{
	t_pixel	pixel;
	t_ray	ray;

	printf("%d degrees = %f radians\n", 90, degrees_to_radians(90));
	setup_camera_angle(&scene->cam);//Can change with movement
	pixel.j = 0;
	while (pixel.j < HEIGHT)//TODO: add multi threading
	{
		pixel.i = 0;
		while (pixel.i < WIDTH)
		{
			ray = get_ray_for_position(pixel, scene->cam);
			pixel.color = trace_color(ray, scene);
			ft_mlx_put_pixel(data, pixel);
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
void	setup_camera_angle(t_cam *cam)
{
	t_vec3	opposite_cam;
	const t_vec3	up_view = {0, 0, 1};
	float	fov_multiplier;
	float	cam_angle;

	cam->orient.direction = vector_normalize(cam->orient.direction);
	opposite_cam = vector_multiply(cam->orient.direction, -1);
	cam->vector_i = vector_cross(opposite_cam,up_view);
	cam->vector_j = vector_cross(opposite_cam, cam->vector_i);
	cam_angle = degrees_to_radians(cam->fov / 2);
	fov_multiplier = 1;
}

/*
 * Returns ray from camera origin to point in 3d coordinates
 */
t_ray	get_ray_for_position(t_pixel pixel, t_cam cam)
{
	t_ray	ray;
	t_vec3	position_width;
	t_vec3	position_heigth;

	position_width = vector_multiply(cam.vector_i, pixel.i - WIDTH / 2);
	position_heigth = vector_multiply(cam.vector_j, pixel.j - HEIGHT / 2);
	ray.origin = cam.orient.origin;
	ray.direction = vector_add(position_width, position_heigth);
	return (ray);
}

// Need to normalize obj, not cam
/*
void	normalize_view(t_scene *scene)
{
	t_olist	*obj_list;
	t_sp	*sp;
	t_cy	*cy;
	t_pl	*pl;

	if (vector_is_zero(scene->cam.orient.origin))//and view is normalized
		return ;
	scene->light.pos = vector_add(scene->cam.orient.origin, scene->light.pos);
	obj_list = scene->obj_list;
	while (obj_list)
	{
		if (obj_list->obj_type == SP)
		{
			sp = (t_sp *)obj_list->obj;
			sp->sp_center = vector_add(scene->cam.orient.origin, sp->sp_center);
		} 
		else if (obj_list->obj_type == CY)
		{
			cy = (t_cy *)obj_list->obj;
			cy->normal = vector_add(scene->cam.orient.origin, cy->normal.origin);
		}
		else if (obj_list->obj_type == PL)
		{
			pl = (t_pl *)obj_list->obj;
			pl->normal = vector_add(scene->cam.orient.origin, pl->normal.origin);
		}
		else
			continue ;
		obj_list = obj_list->next;
	}
	vector_to_zero(&scene->cam.orient.origin);
}
*/

int	trace_color(t_ray ray, t_scene *scene)
{
	t_olist	*obj_list;
	t_sp	*sp;
	t_cy	*cy;
	t_pl	*pl;
	int		color;
	int		distance;
	int		closest;

	color = scene->ambient.colour;
	closest = -1;
	obj_list = scene->obj_list;
	while (obj_list)
	{
		if (obj_list->obj_type == SP)
		{
			sp = (t_sp *)obj_list->obj;
			distance = hit_sp(ray, sp);
			if (is_closest(distance, closest))
				color = sp->colour;
		}
		else if (obj_list->obj_type == CY)
		{
			cy = (t_cy *)obj_list->obj;
			distance = hit_cy(ray, cy);
			if (is_closest(distance, closest))
				color = cy->colour;
		}
		else if (obj_list->obj_type == PL)
		{
			pl = (t_pl *)obj_list->obj;
			distance = hit_pl(ray, pl);
			if (is_closest(distance, closest))
				color = pl->colour;
		}
		else
			continue ;
		obj_list = obj_list->next;
	}
	return (color);
}

bool	is_closest(int distance, int closest)
{
	if (distance > 0 && (closest < 0 || distance < closest))
		return (true);
	return (false);
}

