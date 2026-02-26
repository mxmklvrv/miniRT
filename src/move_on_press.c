#include "minirt.h"

int	key_press_hook(int key, t_data *data)
{
	t_move_state	*move;

	move = data->move_state;
	set_general_keys(key, data);
	set_translation_keys(key, move, KEY_ON);
	set_rotation_keys(key, move, KEY_ON);
	set_resize_keys(key, move, KEY_ON);
	return (0);
}

int	key_release_hook(int key, t_data *data)
{
	t_move_state	*move;

	move = data->move_state;
	set_general_keys(key, data);
	set_translation_keys(key, move, KEY_OFF);
	set_rotation_keys(key, move, KEY_OFF);
	set_resize_keys(key, move, KEY_OFF);
	return (0);
}

int	render_hook(t_data *data)
{
	apply_movement(data);
	return (0);
}

void	set_general_keys(int key, t_data *data)
{
	if (key == KEY_TAB)
		select_object(data->scene);
	else if (key == KEY_C)
	{
		data->control_cam = !data->control_cam;
		printf("controling cam");
	}
	else if (key == KEY_ESC)
		mlx_loop_end(data->mlx);
}

void	set_translation_keys(int key, t_move_state *move, int value)
{
	if (key == KEY_W)
		move->forward = value;
	else if (key == KEY_S)
		move->backward = value;
	else if (key == KEY_A)
		move->left = value;
	else if (key == KEY_D)
		move->right = value;
	else if (key == KEY_Q)
		move->up = value;
	else if (key == KEY_E)
		move->down = value;
}

void	set_rotation_keys(int key, t_move_state *move, int value)
{
	if (key == KEY_LEFT)
		move->rotate_left = value;
	else if (key == KEY_RIGHT)
		move->rotate_right = value;
	else if (key == KEY_UP)
		move->rotate_up = value;
	else if (key == KEY_DOWN)
		move->rotate_down = value;
}

void	set_resize_keys(int key, t_move_state *move, int value)
{
	if (key == KEY_PLUS)
		move->resize_up = value;
	else if (key == KEY_MINUS)
		move->resize_down = value;
	else if (key == KEY_H)
		move->height_up = value;
	else if (key == KEY_J)
		move->height_down = value;
}

/**
 * If there is next obj - select it
 * Otherwise select the first one
 */
void	select_object(t_scene *scene)
{
	if (!scene->obj_selected)
		scene->obj_selected = scene->obj_list;
	else if (scene->obj_selected->next)
		scene->obj_selected = scene->obj_selected->next;
	else
		scene->obj_selected = scene->obj_list;
	printf("controlling obj"); // mb add coords of obj, type, etc
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

void	translate_cam(t_cam *cam, t_vec3 move_vec)
{
	cam->orient.origin = vector_add(cam->orient.origin, move_vec);
	setup_camera_angle(cam);
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

void	apply_movement(t_data *data)
{
	int	need_redraw;

	need_redraw = 0;
	if (handle_translation(data))
		need_redraw = 1;
	if (handle_rotation(data))
		need_redraw = 1;
	if (handle_resize(data))
		need_redraw = 1;
	if (need_redraw)
		redraw_scene(data, data->scene);
}

// add translate light
int	handle_translation(t_data *data)
{
	t_move_state	*move;
	t_vec3			move_vec;

	move = data->move_state;
	move_vec = new_vector(0, 0, 0);
	if (move->forward)
		move_vec.z -= MOVE_SPEED;
	if (move->backward)
		move_vec.z += MOVE_SPEED;
	if (move->left)
		move_vec.x -= MOVE_SPEED;
	if (move->right)
		move_vec.x += MOVE_SPEED;
	if (move->up)
		move_vec.y += MOVE_SPEED;
	if (move->down)
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
// light cannot be rotated
int	handle_rotation(t_data *data)
{
	t_move_state	*move;

	move = data->move_state;
	if (move->rotate_left)
		rotate_obj_or_cam(data, -ROTATE_SPEED, Y_AXIS);
	if (move->rotate_right)
		rotate_obj_or_cam(data, ROTATE_SPEED, Y_AXIS);
	if (move->rotate_up)
		rotate_obj_or_cam(data, -ROTATE_SPEED, X_AXIS);
	if (move->rotate_down)
		rotate_obj_or_cam(data, ROTATE_SPEED, X_AXIS);
	return (move->rotate_left || move->rotate_right || move->rotate_up
		|| move->rotate_down);
}

// need to add light
void	rotate_obj_or_cam(t_data *data, float angle, t_axis axis)
{
	if (data->control_cam)
		rotate_cam(&data->scene->cam, angle, axis);
	else if (data->scene->obj_selected)
		rotate_objects(data->scene->obj_selected, angle, axis);
}

void	rotate_objects(t_olist *node, float angle, t_axis axis)
{
	t_pl	*pl;
	t_cy	*cy;

	if (!node || node->obj_type == SP)
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

//// can we resize light ?? Looks like no
int	handle_resize(t_data *data)
{
	t_move_state	*move;

	move = data->move_state;
	if (!data->scene->obj_selected || data->scene->obj_selected->obj_type == PL
		|| data->control_cam) // or data->light
		return (0);
	if (move->resize_up && resize_diameter(data->scene->obj_selected,
			RESIZE_SPEED))
		return (1);
	if (move->resize_down && resize_diameter(data->scene->obj_selected,
			-RESIZE_SPEED))
		return (1);
	if (move->height_up && resize_height(data->scene->obj_selected,
			RESIZE_SPEED))
		return (1);
	if (move->height_down && resize_height(data->scene->obj_selected,
			-RESIZE_SPEED))
		return (1);
	return (0);
}

// resizing diam of sphere and cy
int	resize_diameter(t_olist *node, float value)
{
	t_sp	*sp;
	t_cy	*cy;

	if (!node || node->obj_type == PL)
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

// void	apply_movement(t_data *data)
// {
// 	t_move_state	*move;
// 	t_vec3			move_vec;
// 	int				need_redraw;

// 	need_redraw = 0;
// 	move = data->move_state;
// 	move_vec = new_vector(0, 0, 0);
// 	if (move->forward)
// 		move_vec = vector_add(move_vec, new_vector(0, 0, -MOVE_SPEED));
// 	if (move->backward)
// 		move_vec = vector_add(move_vec, new_vector(0, 0, MOVE_SPEED));
// 	if (move->left)
// 		move_vec = vector_add(move_vec, new_vector(-MOVE_SPEED, 0, 0));
// 	if (move->right)
// 		move_vec = vector_add(move_vec, new_vector(MOVE_SPEED, 0, 0));
// 	if (move->up)
// 		move_vec = vector_add(move_vec, new_vector(0, MOVE_SPEED, 0));
// 	if (move->down)
// 		move_vec = vector_add(move_vec, new_vector(0, -MOVE_SPEED, 0));
// 	// to check if we pressed smth
// 	if (move_vec.x != 0 || move_vec.y != 0 || move_vec.z != 0)
// 	{
// 		if (data->control_cam)
// 			translate_cam(&data->scene->cam, move_vec);
// 		else if (data->scene->obj_selected)
// 			translate_object(data->scene->obj_selected, move_vec);
// 		need_redraw = 1;
// 	}
// 	if (move->rotate_left)
// 	{
// 		rotate_obj_or_cam(data, -ROTATE_SPEED, Y_AXIS);
// 		need_redraw = 1;
// 	}
// 	if (move->rotate_right)
// 	{
// 		rotate_obj_or_cam(data, ROTATE_SPEED, Y_AXIS);
// 		need_redraw = 1;
// 	}
// 	if (move->rotate_up)
// 	{
// 		rotate_obj_or_cam(data, -ROTATE_SPEED, X_AXIS);
// 		need_redraw = 1;
// 	}
// 	if (move->rotate_down)
// 	{
// 		rotate_obj_or_cam(data, ROTATE_SPEED, X_AXIS);
// 		need_redraw = 1;
// 	}
// 	if (move->resize_up)
// 	{
// 		if (data->scene->obj_selected && !data->control_cam)
// 		{
// 			resize_objects(data->scene->obj_selected, RESIZE_SPEED);
// 			need_redraw = 1;
// 		}
// 	}
// 	if (move->resize_down)
// 	{
// 		if (data->scene->obj_selected && !data->control_cam)
// 		{
// 			resize_objects(data->scene->obj_selected, -RESIZE_SPEED);
// 			need_redraw = 1;
// 		}
// 	}
// 	if (need_redraw)
// 		redraw_scene(data, data->scene);
// }

// int	handle_rotation(t_data *data)
// {
// 	t_move_state	*move;
// 	int				changed;

// 	move = data->move_state;
// 	changed = 0;
// 	if (move->rotate_left)
// 	{
// 		rotate_obj_or_cam(data, -ROTATE_SPEED, Y_AXIS);
// 		changed = 1;
// 	}
// 	if (move->rotate_right)
// 	{
// 		rotate_obj_or_cam(data, ROTATE_SPEED, Y_AXIS);
// 		changed = 1;
// 	}
// 	if (move->rotate_up)
// 	{
// 		rotate_obj_or_cam(data, -ROTATE_SPEED, X_AXIS);
// 		changed = 1;
// 	}
// 	if (move->rotate_down)
// 	{
// 		rotate_obj_or_cam(data, ROTATE_SPEED, X_AXIS);
// 		changed = 1;
// 	}
// 	return (changed);
// }

// void	rotate_objects(t_olist *node, float angle)
// {
// 	t_pl	*pl;
// 	t_cy	*cy;

// 	if (!node || node->obj_type == SP)
// 		return ;
// 	if (node->obj_type == PL)
// 	{
// 		pl = (t_pl *)node->obj;
// 		pl->normal.direction = vector_normalize(rotate_y(pl->normal.direction,
// 					angle));
// 	}
// 	else if (node->obj_type == CY)
// 	{
// 		cy = (t_cy *)node->obj;
// 		cy->normal.direction = vector_normalize(rotate_y(cy->normal.direction,
// 					angle));
// 	}
// }

// void	rotate_objects_x(t_olist *node, float angle)
// {
// 	t_pl	*pl;
// 	t_cy	*cy;

// 	if (!node)
// 		return ;
// 	if (node->obj_type == PL)
// 	{
// 		pl = (t_pl *)node->obj;
// 		pl->normal.direction = vector_normalize(rotate_x(pl->normal.direction,
// 					angle));
// 	}
// 	else if (node->obj_type == CY)
// 	{
// 		cy = (t_cy *)node->obj;
// 		cy->normal.direction = vector_normalize(rotate_x(cy->normal.direction,
// 					angle));
// 	}
// }

// int	key_press_hook(int key, t_data *data)
// {
// 	t_move_state	*move;

// 	move = data->move_state;
// 	if (key == KEY_TAB)
// 		select_object(data->scene);
// 	else if (key == KEY_C)
// 	{
// 		data->control_cam = !data->control_cam;
// 		printf("controling cam");
// 	}
// 	else if (key == KEY_W)
// 		move->forward = 1;
// 	else if (key == KEY_S)
// 		move->backward = 1;
// 	else if (key == KEY_A)
// 		move->left = 1;
// 	else if (key == KEY_D)
// 		move->right = 1;
// 	else if (key == KEY_Q)
// 		move->up = 1;
// 	else if (key == KEY_E)
// 		move->down = 1;
// 	// rotation
// 	else if (key == KEY_LEFT)
// 		move->rotate_left = 1;
// 	else if (key == KEY_RIGHT)
// 		move->rotate_right = 1;
// 	else if (key == KEY_UP)
// 		move->rotate_up = 1;
// 	else if (key == KEY_DOWN)
// 		move->rotate_down = 1;
// 	// resize
// 	else if (key == KEY_PLUS)
// 		move->resize_up = 1;
// 	else if (key == KEY_MINUS)
// 		move->resize_down = 1;
// 	else if (key == KEY_H)
// 		move->height_up = 1;
// 	else if (key == KEY_J)
// 		move->height_down = 1;
// 	else if (key == KEY_ESC)
// 		mlx_loop_end(data->mlx);
// 	return (0);
// }

// int	key_release_hook(int key, t_data *data)
// {
// 	t_move_state	*move;

// 	move = data->move_state;
// 	if (key == KEY_W)
// 		move->forward = 0;
// 	else if (key == KEY_S)
// 		move->backward = 0;
// 	else if (key == KEY_A)
// 		move->left = 0;
// 	else if (key == KEY_D)
// 		move->right = 0;
// 	else if (key == KEY_Q)
// 		move->up = 0;
// 	else if (key == KEY_E)
// 		move->down = 0;
// 	// rotation
// 	else if (key == KEY_LEFT)
// 		move->rotate_left = 0;
// 	else if (key == KEY_RIGHT)
// 		move->rotate_right = 0;
// 	else if (key == KEY_UP)
// 		move->rotate_up = 0;
// 	else if (key == KEY_DOWN)
// 		move->rotate_down = 0;
// 	// size
// 	else if (key == KEY_PLUS)
// 		move->resize_up = 0;
// 	else if (key == KEY_MINUS)
// 		move->resize_down = 0;
// 	// height of cy
// 	else if (key == KEY_H)
// 		move->height_up = 0;
// 	else if (key == KEY_J)
// 		move->height_down = 0;
// 	return (0);
// }