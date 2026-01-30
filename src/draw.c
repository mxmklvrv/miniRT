#include "minirt.h"

//TODO: Check if ray or cam is inside any obj

float	get_zoom(t_cam cam);
t_vec3	get_camera_angle(t_cam cam);
t_ray	get_ray_for_position(t_pixel pixel, t_cam cam);

//void	normalize_pos(t_scene *scene);
int		trace_color(t_ray ray, t_scene *scene);
bool	is_closest(int distance, int closest);

void	draw_scene(t_data *data, t_scene *scene)
{
	t_pixel	pixel;
	//t_ray	ray;

	scene->cam.zoom = get_zoom(scene->cam);//Doesn't change ever(?)
	scene->cam.angle = get_camera_angle(scene->cam);//Can change with movement
	printf("Zoom: %f\nAngle:\nx = %f\ny = %f\nz = %f\n", scene->cam.zoom, 
		scene->cam.angle.x, scene->cam.angle.y, scene->cam.angle.z);
	pixel.j = 0;
	while (pixel.j < HEIGHT)//TODO: add multi threading
	{
		pixel.i = 0;
		while (pixel.i < WIDTH)
		{
			//ray = get_ray_for_position(pixel, scene->cam);
			//pixel.color = trace_color(ray, scene);
			ft_mlx_put_pixel(data, pixel);
			pixel.i++;
		}
		pixel.j++;
	}
}

/*
 * Find how much distance is 1 pixel. Depends on camera field of view,
 * length of camera direction vector and window width or heigth.
 */
float	get_zoom(t_cam cam)
{
	float	zoom;
	float	cam_length;
	float	tan;

	cam_length = vector_length(cam.orient.direction);
	tan = tanf(cam.fov * M_PI / 180 / 2);
	zoom = cam_length * tan * 2 / ft_max(2, WIDTH, 1);
	printf("\nZOOM\nCamera vector len = %f\nAngel = %f\ntan = %f\nZoom = %f\n\n", 
		cam_length, cam.fov / 2, tan, zoom);
	return (zoom);
}

/*
 * Calculate angle (in radians, counter-clockwise) between screen projection
 * and 0x axis on xy plane. This angle is equal to angle between camera normal
 * and 0y axis. If angle is zero screen is parallel to 0x axis and camera
 * normal is parallel to 0y axis.
 * Returns sine and cosine of this angle in form of t_vec3.
 */
t_vec3	get_camera_angle(t_cam cam)
{
	t_vec3	angle;
	float	cam_length;

	angle.x = 0;
	angle.y = 0;
	angle.z = 0;
	cam_length = vector_length(cam.orient.direction);
	if (cam_length != 0)
	{
		angle.x = cam.orient.origin.y / cam_length;
		angle.y = cam.orient.origin.x / cam_length;
		angle.z = cam.orient.origin.z / cam_length;
	}
	return (angle);
}

/*
 * Returns ray from camera origin to point in 3d coordinates
 */
t_ray	get_ray_for_position(t_pixel pixel, t_cam cam)
{
	t_ray	ray;
	t_vec3	position;
	float	position_width;
	float	position_heigth;

	position_width = (float)(pixel.i - WIDTH / 2) * cam.zoom;
	position_heigth = (float)(pixel.j - HEIGHT / 2) * cam.zoom;
	position.x = position_width * cam.angle.x;
	position.y = position_width * cam.angle.y;
	position.z = position_heigth * cam.angle.z;
	ray.origin = cam.orient.origin;
	ray.direction = vector_add(cam.orient.direction, position);
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
			{
				color = pl->colour;
				printf("Found a plane, color: %d\n", color);
			}
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

