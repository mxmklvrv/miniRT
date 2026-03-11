#include "minirt.h"

// // test functions

void	reset_move_state(t_move_state *move)
{
	ft_bzero(move, sizeof(t_move_state));
}

//
// === 1. ADD THESE HELPER FUNCTIONS (put them near your other vector functions,
// t_vec3	camera_forward(t_cam *cam)
// {
// 	return (vector_normalize(cam->orient.direction));
// }

// t_vec3	camera_right(t_cam *cam)
// {
// 	t_vec3	forward;
// 	t_vec3	world_up;
// 	t_vec3	right;

// 	forward = camera_forward(cam);
// 	world_up = new_vector(0, 1, 0);
// 	right = vector_cross(world_up, forward); // right = vector_cross(world_up, forward);
// 	// fallback if camera is looking straight up/down (prevents zero vector)
// 	if (vector_magnitude(right) < 0.01f)
// 		right = new_vector(1, 0, 0);
// 	return (vector_normalize(right));
// }
// int	handle_translation(t_data *data)
// {
// 	t_move_state	*move;
// 	t_vec3			move_vec;
// 	float			speed;
// 	t_vec3			fwd;
// 	t_vec3			right;

// 	move = data->move_state;
// 	move_vec = new_vector(0, 0, 0);
// 	speed = MOVE_SPEED;
// 	if (data->control_cam)
// 	{
// 		// CAMERA MOVEMENT = camera-relative (what your teammate expects)
// 		fwd = camera_forward(&data->scene->cam);
// 		right = camera_right(&data->scene->cam);
// 		// now move up move->forward (W) vert
// 		if (move->forward)
// 			move_vec.y += speed;
// 		// now move down move->backword (S) vert
// 		if (move->backward)
// 			move_vec.y -= speed;
// 		if (move->left)
// 			move_vec = vector_add(move_vec, vector_multiply(right, -speed));
// 		// A = left
// 		if (move->right)
// 			move_vec = vector_add(move_vec, vector_multiply(right, speed));
// 		// D = right
// 		// now Q moves up
// 		if (move->up)
// 			move_vec = vector_add(move_vec, vector_multiply(fwd, speed));
// 		// now E moves down
// 		if (move->down)
// 			move_vec = vector_add(move_vec, vector_multiply(fwd, -speed));
// 	}
// 	else if (data->scene->obj_selected)
// 	{
// 		// OBJECT MOVEMENT = world space (standard for selected objects in miniRT)
// 		// This fixes "W moves object up" and "Q/E moves it closer/farther"
// 		if (move->forward)
// 			move_vec.z -= speed;
// 		if (move->backward)
// 			move_vec.z += speed;
// 		if (move->left)
// 			move_vec.x -= speed;
// 		if (move->right)
// 			move_vec.x += speed;
// 		if (move->up)
// 			move_vec.y += speed;
// 		if (move->down)
// 			move_vec.y -= speed;
// 	}
// 	if (move_vec.x != 0 || move_vec.y != 0 || move_vec.z != 0)
// 	{
// 		if (data->control_cam)
// 			translate_cam(&data->scene->cam, move_vec);
// 		else
// 			translate_object(data->scene->obj_selected, move_vec);
// 		return (1);
// 	}
// 	return (0);
// }


int	key_press_hook(int key, t_data *data)
{
	t_move_state	*move;

	move = data->move_state;
	// print_pos(data->scene); // test
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
	if (key != KEY_C && key != KEY_TAB && key != KEY_ESC)
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
	{

		reset_move_state(data->move_state);

		if (data->control_cam == 1)
		{
			data->control_cam = 0;
			print_pos(data->scene);
		}
		else
			select_object(data);
	}
	if (key == KEY_C)
	{
		reset_move_state(data->move_state);

		data->control_cam = !data->control_cam;
		if (data->control_cam == 0)
			print_pos(data->scene);
		else
			print_cam_pos(data->scene);
	}
	if (key == KEY_ESC)
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
	t_shape	*obj;

	if (!node || !node->shape)
		return ;
	obj = node->shape;
	if (obj->obj_type == SP)
		obj->center = vector_add(obj->center, move_vec);
	else if (obj->obj_type == PL)
		obj->normal.origin = vector_add(obj->normal.origin, move_vec);
	else if (obj->obj_type == CY)
		obj->normal.origin = vector_add(obj->normal.origin, move_vec);
}

void	translate_cam(t_cam *cam, t_vec3 move_vec)
{
	cam->orient.origin = vector_add(cam->orient.origin, move_vec);
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

// void	rotate_cam(t_cam *cam, float angle, t_axis axis)
// {
// 	if (axis == Y_AXIS)
// 	{
// 		cam->yaw += angle;
// 		// Keep yaw within 0-2PI range
// 	}
// 	else if (axis == X_AXIS)
// 	{
// 		cam->pitch += angle;
// 		// Clamp pitch to avoid flipping
// 		if (cam->pitch > 89.0f * M_PI / 180.0f)
// 			cam->pitch = 89.0f * M_PI / 180.0f;
// 		if (cam->pitch < -89.0f * M_PI / 180.0f)
// 			cam->pitch = -89.0f * M_PI / 180.0f;
// 	}

// 	// Recalculate direction from yaw and pitch
// 	cam->orient.direction.x = cosf(cam->yaw) * cosf(cam->pitch);
// 	cam->orient.direction.y = sinf(cam->pitch);
// 	cam->orient.direction.z = sinf(cam->yaw) * cosf(cam->pitch);
// 	cam->orient.direction = vector_normalize(cam->orient.direction);

// 	setup_camera_angle(cam);
// }



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
		redraw_scene(data);
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


//&& data->control_cam == 0 	// and light here as well
int	is_exeption(t_data *data, t_exeption action)
{
	if (action == NO_ROT)
	{
		if (data->scene->obj_selected->shape->obj_type == SP
			&& data->control_cam == 0)
			return (1);
	}
	if (action == NO_RES)
	{
		if (data->scene->obj_selected->shape->obj_type == PL
			|| data->control_cam)
			// add light here
			return (1);
	}
	if (action == NO_HIGHT_RES)
	{
		if (data->control_cam
			|| data->scene->obj_selected->shape->obj_type != CY) // add light
			// should be &&
			// add light
			return (1);
	}
	return (0);
}

// light cannot be rotated
int	handle_rotation(t_data *data)
{
	t_move_state	*move;

	if (!data)
		return (0);
	move = data->move_state;
	if (is_exeption(data, NO_ROT))
		return (0);
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
	t_shape	*obj;

	if (!node || !node->shape)
		return ;
	obj = node->shape;
	if (obj->obj_type == PL || obj->obj_type == CY)
	{
		if (axis == Y_AXIS)
			obj->normal.direction = vector_normalize(rotate_y(obj->normal.direction,
						angle));
		else
			obj->normal.direction = vector_normalize(rotate_x(obj->normal.direction,
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

	if (!data->scene) // or data->light
		return (0);
	move = data->move_state;
	if (move->resize_up && !is_exeption(data, NO_RES)
		&& resize_diameter(data->scene->obj_selected, RESIZE_SPEED))
		return (1);
	if (move->resize_down && !is_exeption(data, NO_RES)
		&& resize_diameter(data->scene->obj_selected, -RESIZE_SPEED))
		return (1);
	if (move->height_up && !is_exeption(data, NO_HIGHT_RES)
		&& resize_height(data->scene->obj_selected, RESIZE_SPEED))
		return (1);
	if (move->height_down && !is_exeption(data, NO_HIGHT_RES)
		&& resize_height(data->scene->obj_selected, -RESIZE_SPEED))
		return (1);
	return (0);
}

int	resize_diameter(t_olist *node, float value)
{
	t_shape	*obj;

	if (!node || !node->shape)
		return (0);
	obj = node->shape;
	if (obj->obj_type == SP || obj->obj_type == CY)
	{
		obj->diameter += value;
		if (obj->diameter < 0.1f)
			obj->diameter = 0.1f;
		return (1);
	}
	return (0);
}

int	resize_height(t_olist *node, float value)
{
	t_shape	*obj;

	if (!node || !node->shape)
		return (0);
	obj = node->shape;
	obj->height += value;
	if (obj->height < 0.1f)
		obj->height = 0.1f;
	return (1);
}
