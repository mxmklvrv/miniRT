#include "minirt.h"

//TODO: Check if ray or cam is inside any obj

float	get_zoom(t_scene *scene)

//static void	normalize_pos(t_scene *scene);
static int	trace_color(t_pixel pixel, t_scene *scene);
static bool	is_closest(int *distance, int *closest);

void	draw_scene(t_data *data, t_scene *scene)
{
	t_pixel	pixel;
	t_ray	ray;

	scene->zoom = get_zoom(scene);
	scene->cam.angle = get_camera_angle(scene->cam);
	pixel.y = 0;
	while (pixel.y < HEIGHT)//TODO: add multi threading
	{
		pixel.x = 0;
		while (pixel.x < WIDTH)
		{
			ray = get_ray_for_position(pixel, scene->cam);
			pixel.color = trace_color(ray, scene);
			ft_mlx_put_pixel(data, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
}

/*
 * Find how much distance is 1 pixel. Depends on camera field of view,
 * length of camera direction vector and window width or heigth.
 */
float	get_zoom(t_scene *scene)
{
	return (vector_length(scene->cam.orient.direction)
		* tanf(scene->cam.fov / 2) * 2 / ft_max(3, WIDTH, HIGHT, 1);
}

/*
 * Calculate angle between screen projection and 0x axis on xy plane. If angle
 * is zero screen is parallel to xy plane; it is then positioned with WIDTH
 * aligned with 0x axis.
 */
float	get_camera_angle(t_cam cam)
{
	float	angle;
	float	x;
	float	y;

	x = cam.orient.position.x;
	y = cam.orient.position.y;
	if (x == 0 && y >= 0)
		return (0);
	if (x == 0 && y < 0)
		return (PI);
	if (y == 0 && x > 0)
		return (PI / 2);
	if (y == 0 && x < 0)
		return (-Pi / 2);
	return (arcsin())
}

t_ray	get_ray_for_position(t_point pixel, t_cam cam)
{
	t_ray	ray;
	t_vec3	pos;

	ray.direction = cam.orient.direction;
	
	return (ray);
}

// Need to normalize obj, not cam
/*
static void	normalize_view(t_scene *scene)
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

static int	trace_color(t_ray ray, t_scene *scene)
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
			distance = hit_sp(scene->cam.orient.direction, sp);
			if (is_closest(&distance, &closest))
				color = sp->colour;
		}
		else if (obj_list->obj_type == CY)
		{
			cy = (t_cy *)obj_list->obj;
			distance = hit_cy(scene->cam.view_point, cy);
			if (is_closest(&distance, &closest))
				color = cy->colour;
		}
		else if (obj_list->obj_type == PL)
		{
			pl = (t_pl *)obj_list->obj;
			distance = hit_pl(scene->cam.view_point, pl);
			if (is_closest(&distance, &closest))
				color = pl->colour;
		}
		else
			continue ;
		obj_list = obj_list->next;
	}
	return (color);
}

static bool	is_closest(int *distance, int *closest)
{
	if (distance > 0 && (closest < 0 || distance < closest))
		return (true);
	return (false);
}

