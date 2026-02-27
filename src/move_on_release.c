#include "minirt.h"

int	key_press_hook(int key, t_data *data)
{
	// printf("scene ptr: %p\n", data->scene);
	// printf("Key pressed: %d\n", key);
	if (key == KEY_C)
	{
		data->control_cam = !data->control_cam;
		if (data->control_cam == 0)
			print_pos(data->scene);
		else
			print_cam_pos(data->scene);
	}
	else if (key == KEY_TAB)
	{
		if(data->control_cam == 1)
		{
			data->control_cam = 0;
			print_pos(data->scene);
		}
		else
			select_object(data);
	}
	else if (key == KEY_ESC)
		mlx_loop_end(data->mlx);
	return (0);
}
// clean version
// int	key_release_hook(int key, t_data *data)
// {
// 	int	need_redraw;

// 	need_redraw = 0;
// 	if (handle_translation(key, data))
// 		need_redraw = 1;
// 	if (handle_rotation(key, data))
// 		need_redraw = 1;
// 	if (handle_resize(key, data))
// 		need_redraw = 1;
// 	if (need_redraw)
// 		redraw_scene(data, data->scene);
// 	return (0);
// }

// DIRTY VERSION
int	key_release_hook(int key, t_data *data)
{
	int	need_redraw;

	need_redraw = 0;
	if (handle_translation(key, data))
	{
		if (data->control_cam == 1)
			print_cam_pos(data->scene);
		else
			print_pos(data->scene);
		need_redraw = 1;
	}
	if (handle_rotation(key, data))
	{
		if (data->control_cam == 1)
			print_cam_pos(data->scene);
		else
			print_pos(data->scene);
		need_redraw = 1;
	}
	if (handle_resize(key, data))
	{
		if (data->control_cam == 1)
			print_cam_pos(data->scene);
		else
			print_pos(data->scene);
		need_redraw = 1;
	}
	if (need_redraw)
		redraw_scene(data, data->scene);
	return (0);
}

// add translate light
// clean version
int	handle_translation(int key, t_data *data)
{
	t_vec3	move_vec;

	move_vec = new_vector(0, 0, 0);
	if (key == KEY_W)
		move_vec.z -= MOVE_SPEED;
	else if (key == KEY_S)
		move_vec.z += MOVE_SPEED;
	else if (key == KEY_A)
		move_vec.x -= MOVE_SPEED;
	else if (key == KEY_D)
		move_vec.x += MOVE_SPEED;
	else if (key == KEY_Q)
		move_vec.y += MOVE_SPEED;
	else if (key == KEY_E)
		move_vec.y -= MOVE_SPEED;
	if (move_vec.x != 0 || move_vec.y != 0 || move_vec.z != 0)
	{
		if (data->control_cam)
			translate_cam(&data->scene->cam, move_vec);
		else if (data->scene->obj_selected)
			translate_object(data->scene->obj_selected, move_vec);
		return (1);
	}
	return (0);
}

// can we resize light ?? Looks like no
// cannot resize pl
// cannot resize cam

// light cannot be rotated
// sphere cannot be rotated
int	is_exeption(t_data *data, t_exeption action)
{
	if (action == NO_ROT)
	{
		if (data->scene->obj_selected->obj_type == SP && !data->control_cam) // and light here as well
			return (1);
	}
	if (action == NO_RES)
	{
		if (data->scene->obj_selected->obj_type == PL || data->control_cam)
			// add light here
			return (1);
	}
	if (action == NO_HIGHT_RES)
		if (data->control_cam || data->scene->obj_selected->obj_type != CY) // add light // should be &&
			return (1);
	return (0);
}

// light cannot be rotated
// sphere cannot be rotated
int	handle_rotation(int key, t_data *data)
{
	if (is_exeption(data, NO_ROT))
		return (0);
	if (key == KEY_LEFT)
	{
		rotate_obj_or_cam(data, -ROTATE_SPEED, Y_AXIS);
		return (1);
	}
	if (key == KEY_RIGHT)
	{
		rotate_obj_or_cam(data, ROTATE_SPEED, Y_AXIS);
		return (1);
	}
	if (key == KEY_UP)
	{
		rotate_obj_or_cam(data, -ROTATE_SPEED, X_AXIS);
		return (1);
	}
	if (key == KEY_DOWN)
	{
		rotate_obj_or_cam(data, ROTATE_SPEED, X_AXIS);
		return (1);
	}
	return (0);
}

// can we resize light ?? Looks like no
// cannot resize pl
// cannot resize cam
int	handle_resize(int key, t_data *data)
{
	if (!data->scene->obj_selected)
		return (0); // or data->light // !data || !data->scene ||
	if (key == KEY_PLUS && !is_exeption(data, NO_RES)
		&& resize_diameter(data->scene->obj_selected, RESIZE_SPEED))
		return (1);
	if (key == KEY_MINUS && !is_exeption(data, NO_RES)
		&& resize_diameter(data->scene->obj_selected, -RESIZE_SPEED))
		return (1);
	if (key == KEY_H && !is_exeption(data, NO_HIGHT_RES)
		&& resize_height(data->scene->obj_selected, RESIZE_SPEED))
		return (1);
	if (key == KEY_J && !is_exeption(data, NO_HIGHT_RES)
		&& resize_height(data->scene->obj_selected, -RESIZE_SPEED))
		return (1);
	return (0);
}

// need to add light
void	rotate_obj_or_cam(t_data *data, float angle, t_axis axis)
{
	if (data->control_cam)
		rotate_cam(&data->scene->cam, angle, axis);
	else if (data->scene->obj_selected)
		rotate_objects(data->scene->obj_selected, angle, axis);
}

/**
 * If there is next obj - select it
 * Otherwise select the first one
 */
void	select_object(t_data *data)
{
	if (!data->scene->obj_selected)
		data->scene->obj_selected = data->scene->obj_list;
	else if (data->scene->obj_selected->next)
		data->scene->obj_selected = data->scene->obj_selected->next;
	else
		data->scene->obj_selected = data->scene->obj_list;
	print_pos(data->scene);
}

// need to create move bector with new_vec
void	translate_object(t_olist *node, t_vec3 move_vec)
{
	t_sp	*sp;
	t_pl	*pl;
	t_cy	*cy;

	if (!node)
		return ;
	if (node->obj_type == SP)
	{
		sp = (t_sp *)node->obj;
		sp->sp_center = vector_add(sp->sp_center, move_vec);
	}
	else if (node->obj_type == PL)
	{
		pl = (t_pl *)node->obj;
		pl->normal.origin = vector_add(pl->normal.origin, move_vec);
	}
	else if (node->obj_type == CY)
	{
		cy = (t_cy *)node->obj;
		cy->normal.origin = vector_add(cy->normal.origin, move_vec);
	}
}

void	rotate_objects(t_olist *node, float angle, t_axis axis)
{
	t_pl	*pl;
	t_cy	*cy;

	if (!node)
		return ;
	if (node->obj_type == PL)
	{
		pl = (t_pl *)node->obj;
		if (axis == Y_AXIS)
			pl->normal.direction = vector_normalize(rotate_y(pl->normal.direction,
						angle));
		else
			pl->normal.direction = vector_normalize(rotate_x(pl->normal.direction,
						angle));
	}
	else if (node->obj_type == CY)
	{
		cy = (t_cy *)node->obj;
		if (axis == Y_AXIS)
			cy->normal.direction = vector_normalize(rotate_y(cy->normal.direction,
						angle));
		else
			cy->normal.direction = vector_normalize(rotate_x(cy->normal.direction,
						angle));
	}
}

void	rotate_cam(t_cam *cam, float angle, t_axis axis)
{
	if (axis == Y_AXIS)
		cam->orient.direction = vector_normalize(rotate_y(cam->orient.direction,
					angle));
	else if (axis == X_AXIS)
		cam->orient.direction = vector_normalize(rotate_x(cam->orient.direction,
					angle));
	setup_camera_angle(cam);
}

void	translate_cam(t_cam *cam, t_vec3 move_vec)
{
	cam->orient.origin = vector_add(cam->orient.origin, move_vec);
	setup_camera_angle(cam);
}

// resizing diam of sp and cy
int	resize_diameter(t_olist *node, float value)
{
	t_sp	*sp;
	t_cy	*cy;

	if (!node)
		return (0);
	if (node->obj_type == SP)
	{
		sp = (t_sp *)node->obj;
		sp->diameter += value;
		if (sp->diameter < 0.1f)
			sp->diameter = 0.1f;
	}
	else if (node->obj_type == CY)
	{
		cy = (t_cy *)node->obj;
		cy->diameter += value;
		if (cy->diameter < 0.1f)
			cy->diameter = 0.1f;
	}
	return (1);
}

int	resize_height(t_olist *node, float value)
{
	t_cy	*cy;

	if (!node || node->obj_type != CY)
		return (0);
	cy = (t_cy *)node->obj;
	cy->height += value;
	if (cy->height < 0.1f)
		cy->height = 0.1f;
	return (1);
}

t_vec3	rotate_y(t_vec3 current, float angle)
{
	t_vec3	rotated;
	float	cosinus;
	float	sinus;

	cosinus = cosf(angle);
	sinus = sinf(angle);
	rotated.x = current.x * cosinus + current.z * sinus;
	rotated.y = current.y;
	rotated.z = -current.x * sinus + current.z * cosinus;
	rotated.w = current.w;
	return (rotated);
}

t_vec3	rotate_x(t_vec3 current, float angle)
{
	t_vec3	rotated;
	float	cosinus;
	float	sinus;

	cosinus = cosf(angle);
	sinus = sinf(angle);
	rotated.x = current.x;
	rotated.y = current.y * cosinus - current.z * sinus;
	rotated.z = current.y * sinus + current.z * cosinus;
	rotated.w = current.w;
	return (rotated);
}

void	print_pos(t_scene *scene)
{
	t_olist	*node;
	t_sp	*sp;
	t_pl	*pl;
	t_cy	*cy;

	if (!scene)
		return ;
	node = scene->obj_selected;
	if (!node)
	{
		printf("No object selected\n");
		return ;
	}
	if (node->obj_type == SP)
	{
		sp = (t_sp *)node->obj;
		printf("Controlling Sphere, coordinates: x=%.2f y=%.2f z=%.2f\n", sp->sp_center.x,
			sp->sp_center.y, sp->sp_center.z);
	}
	else if (node->obj_type == PL)
	{
		pl = (t_pl *)node->obj;
		printf("Controlling Plane, coordinates: x=%.2f y=%.2f z=%.2f\n", pl->normal.origin.x,
			pl->normal.origin.y, pl->normal.origin.z);
	}
	else if (node->obj_type == CY)
	{
		cy = (t_cy *)node->obj;
		printf("Contrlling Cylinder, coordinates: x=%.2f y=%.2f z=%.2f\n", cy->normal.origin.x,
			cy->normal.origin.y, cy->normal.origin.z);
	}
}

void	print_cam_pos(t_scene *scene)
{
	if (!scene)
	{
		printf("YOLO");
		return ;
	}
	printf("Controlling Cam, origin: x=%.2f y=%.2f z=%.2f", scene->cam.orient.origin.x,
		scene->cam.orient.origin.y, scene->cam.orient.origin.z);
	printf(" and direct: x=%.2f y=%.2f z=%.2f\n", scene->cam.orient.direction.x,
		scene->cam.orient.direction.y, scene->cam.orient.direction.z);
}