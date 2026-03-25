#include "minirt.h"

static void	update_cy_geo(t_shape *cy);
static void	switch_to_obj(t_data *data);
static void	toggle_cam(t_data *data);
static void	toggle_light(t_data *data);

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
		if (data->control_cam || data->control_light)
			switch_to_obj(data);
		else
			select_object(data);
	}
	else if (key == KEY_C)
		toggle_cam(data);
	else if (key == KEY_L)
		toggle_light(data);
	if (key == KEY_ESC)
		mlx_loop_end(data->mlx);
}

static void	switch_to_obj(t_data *data)
{
	data->control_cam = 0;
	data->control_light = 0;
	print_pos(data->scene);
}

static void	toggle_cam(t_data *data)
{
	data->control_cam = !data->control_cam;
	data->control_light = 0;
	if (data->control_cam)
		print_cam_light_pos(data);
	else
		print_pos(data->scene);
}

static void	toggle_light(t_data *data)
{
	if (data->scene->qt_light == 0)
		return ;
	data->control_light = !data->control_light;
	data->control_cam = 0;
	if (data->control_light)
		print_cam_light_pos(data);
	else
		print_pos(data->scene);
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

void	translate_light(t_light *light, t_vec3 move_vec)
{
	if (!light)
		return ;
	light->pos = vector_add(light->pos, move_vec);
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
		redraw_scene(data);
}

int	handle_translation(t_data *data)
{
	t_move_state	*move;
	t_vec3			move_vec;

	move = data->move_state;
	move_vec = new_vector(0, 0, 0);
	if (data->control_cam)
		cam_move_calculation(data, &move_vec, move);
	else if (data->control_light)
		obj_move_calculation(&move_vec, move);
	else
		obj_move_calculation(&move_vec, move);
	if (move_vec.x != 0 || move_vec.y != 0 || move_vec.z != 0)
	{
		if (data->control_cam)
			translate_cam(&data->scene->cam, move_vec);
		else if (data->control_light)
			translate_light(&data->scene->light, move_vec);
		else if (data->scene->obj_selected)
			translate_object(data->scene->obj_selected, move_vec);
		return (1);
	}
	return (0);
}
void	cam_move_calculation(t_data *data, t_vec3 *move_vec, t_move_state *move)
{
	if (move->forward)
		*move_vec = vector_add(*move_vec,
				vector_multiply(data->scene->cam.orient.direction, MOVE_SPEED));
	if (move->backward)
		*move_vec = vector_add(*move_vec,
				vector_multiply(data->scene->cam.orient.direction,
					-MOVE_SPEED));
	if (move->left)
		*move_vec = vector_add(*move_vec,
				vector_multiply(data->scene->cam.right, -MOVE_SPEED));
	if (move->right)
		*move_vec = vector_add(*move_vec,
				vector_multiply(data->scene->cam.right, MOVE_SPEED));
	if (move->up)
		*move_vec = vector_add(*move_vec, vector_multiply(data->scene->cam.up,
					MOVE_SPEED));
	if (move->down)
		*move_vec = vector_add(*move_vec, vector_multiply(data->scene->cam.up,
					-MOVE_SPEED));
}

void	obj_move_calculation(t_vec3 *move_vec, t_move_state *move)
{
	if (move->forward)
		move_vec->z += MOVE_SPEED;
	if (move->backward)
		move_vec->z -= MOVE_SPEED;
	if (move->left)
		move_vec->x -= MOVE_SPEED;
	if (move->right)
		move_vec->x += MOVE_SPEED;
	if (move->up)
		move_vec->y += MOVE_SPEED;
	if (move->down)
		move_vec->y -= MOVE_SPEED;
}

int	is_exeption(t_data *data, t_exeption action)
{
	t_olist	*selected;

	if (!data || !data->scene)
		return (1);
	selected = data->scene->obj_selected;
	if (data->control_light)
		return (1);
	if (data->control_cam)
	{
		if (action == NO_RES || action == NO_HIGHT_RES)
			return (1);
		return (0);
	}
	if (!selected || !selected->shape)
		return (1);
	if (action == NO_ROT && selected->shape->obj_type == SP)
		return (1);
	if (action == NO_RES && selected->shape->obj_type == PL)
		return (1);
	if (action == NO_HIGHT_RES && selected->shape->obj_type != CY)
		return (1);
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
		rotate_obj_or_cam(data, ROTATE_SPEED, X_AXIS);
	if (move->rotate_down)
		rotate_obj_or_cam(data, -ROTATE_SPEED, X_AXIS);
	return (move->rotate_left || move->rotate_right || move->rotate_up
		|| move->rotate_down);
}

// need to add light
void	rotate_obj_or_cam(t_data *data, float angle, t_axis axis)
{
	t_cam	*cam;

	if (data->control_cam)
	{
		cam = &data->scene->cam;
		if (axis == Y_AXIS)
			cam->yaw += angle;
		else if (axis == X_AXIS)
			cam->pitch += angle;
		// prevents flip on pitch
		if (cam->pitch > 1.55f)
			cam->pitch = 1.55f;
		if (cam->pitch < -1.55f)
			cam->pitch = -1.55f;
		setup_camera_angle(cam);
	}
	else if (data->scene->obj_selected)
		rotate_objects(data->scene->obj_selected, angle, axis);
}

void	rotate_objects(t_olist *node, float angle, t_axis axis)
{
	t_shape	*obj;

	if (!node || !node->shape)
		return ;
	obj = node->shape;
	if (obj->obj_type == PL)
	{
		if (axis == Y_AXIS)
			obj->normal.direction = vector_normalize(rotate_z(obj->normal.direction,
						angle));
		else
			obj->normal.direction = vector_normalize(rotate_x(obj->normal.direction,
						angle));
	}
	else if (obj->obj_type == CY)
	{
		if (axis == Y_AXIS)
			obj->axis = vector_normalize(rotate_z(obj->axis, angle));
		else
			obj->axis = vector_normalize(rotate_x(obj->axis, angle));
	}
}

/* To look up-down we change Z and Y coordinates, so rotate around 0X axis;
 * To look left-right we change X and Y coordinates, so rotate around 0Z axis;
 * Should it be named rotate_z?
 */
// anna
t_vec3	rotate_z(t_vec3 current, float angle)
{
	t_vec3	rotated;
	float	cosinus;
	float	sinus;

	cosinus = cosf(angle);
	sinus = sinf(angle);
	rotated.x = current.x * cosinus + current.y * sinus;
	rotated.y = -current.x * sinus + current.y * cosinus;
	rotated.z = current.z;
	rotated.w = current.w;
	return (rotated);
}

/* Changed 'angle' to '-angle' to invert vertical rotation.
 */
// anna
t_vec3	rotate_x(t_vec3 current, float angle)
{
	t_vec3	rotated;
	float	cosinus;
	float	sinus;

	cosinus = cosf(-angle); // anna
	sinus = sinf(-angle);   // anna
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
		if (obj->obj_type == CY)
			update_cy_geo(obj);
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
	update_cy_geo(obj);
	return (1);
}

static void	update_cy_geo(t_shape *cy)
{
	if (!cy || cy->obj_type != CY)
		return ;
	cy->radius = cy->diameter / 2.0f;
	cy->half_h = cy->height / 2.0f;
}