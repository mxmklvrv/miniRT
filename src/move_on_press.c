#include "minirt.h"

// // test functions

void	reset_move_state(t_move_state *move)
{
	ft_bzero(move, sizeof(t_move_state));
}

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
		move->up = value;
	else if (key == KEY_S)
		move->down = value;
	else if (key == KEY_A)
		move->left = value;
	else if (key == KEY_D)
		move->right = value;
	else if (key == KEY_Q)
		move->forward = value;
	else if (key == KEY_E)
		move->backward = value;
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

void	apply_movement(t_data *data)
{
	int	need_redraw;

	need_redraw = 0;
    if(data->control_cam)
    {
        if(handle_translation_cam(data))
            need_redraw = 1;
    }
    else
    {
        if (handle_translation(data))
		    need_redraw = 1;
    }
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
		 if (data->scene->obj_selected)
			translate_object(data->scene->obj_selected, move_vec);
		return (1);
	}
	return (0);
}

// Updates orient.direction based on yaw/pitch
void update_cam_direction(t_cam *cam)
{
    cam->orient.direction.x = cosf(cam->pitch) * sinf(cam->yaw);
    cam->orient.direction.y = sinf(cam->pitch);
    cam->orient.direction.z = cosf(cam->pitch) * cosf(cam->yaw);
    cam->orient.direction = vector_normalize(cam->orient.direction);
}

void rotate_cam_yaw_pitch(t_cam *cam, float yaw_delta, float pitch_delta)
{
    cam->yaw += yaw_delta;
    cam->pitch += pitch_delta;

    // Clamp pitch to avoid flipping
    if (cam->pitch > M_PI_2 - 0.01f)
        cam->pitch = M_PI_2 - 0.01f;
    if (cam->pitch < -M_PI_2 + 0.01f)
        cam->pitch = -M_PI_2 + 0.01f;

    update_cam_direction(cam);
}

int handle_translation_cam(t_data *data)
{
    t_vec3 move_vec;
    t_vec3 forward;
    t_vec3 right;
    t_vec3 up;
    t_move_state *move;

    move = data->move_state;
    forward = cam_forward(&data->scene->cam);
    right   = cam_right(&data->scene->cam);
    up      = cam_up(&data->scene->cam);

    move_vec = new_vector(0, 0, 0);

    if(move->forward)
        move_vec = vector_add(move_vec, vector_multiply(forward, MOVE_SPEED));
    if(move->backward)
        move_vec = vector_add(move_vec, vector_multiply(forward, -MOVE_SPEED));
    if(move->left)
        move_vec = vector_add(move_vec, vector_multiply(right, -MOVE_SPEED));
    if(move->right)
        move_vec = vector_add(move_vec, vector_multiply(right, MOVE_SPEED));
    if(move->up)
        move_vec = vector_add(move_vec, vector_multiply(up, MOVE_SPEED));
    if(move->down)
        move_vec = vector_add(move_vec, vector_multiply(up, -MOVE_SPEED));
    if(vector_magnitude(move_vec) > 0)
    {
        translate_cam(&data->scene->cam, move_vec);
        return(1);
    }
    return (0);
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

// test cam functions


t_vec3 cam_forward(t_cam *cam) { return vector_normalize(cam->orient.direction); }

t_vec3 cam_right(t_cam *cam)
{
    t_vec3 world_up = new_vector(0, 1, 0);

    if (fabsf(vector_dot(cam->orient.direction, world_up)) > 0.99f)
        world_up = new_vector(0, 0, 1);

    t_vec3 right = vector_cross(world_up, cam->orient.direction);

    return vector_normalize(right);
}

t_vec3 cam_up(t_cam *cam)
{
    return vector_normalize(vector_cross(cam->orient.direction, cam_right(cam)));
}


t_vec3 rotate_around_axis(t_vec3 v, t_vec3 axis, float angle)
{
    t_vec3 k = vector_normalize(axis);
    t_vec3 v_rot;
    float cos_theta = cosf(angle);
    float sin_theta = sinf(angle);

    t_vec3 cross = vector_cross(k, v);
    float dot = vector_dot(k, v);

    v_rot = vector_add(
        vector_add(
            vector_multiply(v, cos_theta),      // v * cos(theta)
            vector_multiply(cross, sin_theta)   // (k x v) * sin(theta)
        ),
        vector_multiply(k, dot * (1 - cos_theta)) // k * (k . v) * (1 - cos(theta))
    );
    return v_rot;
}


// void rotate_cam_angles(t_cam *cam, float yaw_delta, float pitch_delta)
// {
//     cam->yaw += yaw_delta;
//     cam->pitch += pitch_delta;

//     // Optional: clamp pitch to avoid flipping upside down
//     // float max_pitch = M_PI_2 - 0.01f; // ~89 degrees
//     // if(cam->pitch > max_pitch) cam->pitch = max_pitch;
//     // if(cam->pitch < -max_pitch) cam->pitch = -max_pitch;

//     // Update camera forward vector
//     cam->orient.direction = cam_forward(cam);

//     // Recompute pixel size / matrices if needed
//     setup_camera_angle(cam);
// }

void rotate_object_local(t_shape *obj, float angle, t_axis axis)
{
    if (!obj)
        return;
    if (obj->obj_type == PL || obj->obj_type == CY)
    {
        if (axis == Y_AXIS)
            obj->normal.direction = vector_normalize(
                rotate_around_axis(obj->normal.direction, new_vector(0,1,0), angle)
            );
        else if (axis == X_AXIS)
            obj->normal.direction = vector_normalize(
                rotate_around_axis(obj->normal.direction, new_vector(1,0,0), angle)
            );
    }
}

void rotate_obj_or_cam(t_data *data, float angle, t_axis axis)
{
    if(data->control_cam)
    {
        t_cam *cam = &data->scene->cam;
        if(axis == Y_AXIS)       // LEFT/RIGHT
            rotate_cam_yaw_pitch(cam, angle, 0);
        else if(axis == X_AXIS)  // UP/DOWN
            rotate_cam_yaw_pitch(cam, 0, angle);
    }
    else if(data->scene->obj_selected)
    {
        rotate_object_local(data->scene->obj_selected->shape, angle, axis);
    }
}


int handle_rotation(t_data *data)
{
    t_move_state *move = data->move_state;

    if (!data || !move)
        return 0;

    int rotated = 0;

    if (move->rotate_left) {
        rotate_obj_or_cam(data, -ROTATE_SPEED, Y_AXIS);
        rotated = 1;
    }
    if (move->rotate_right) {
        rotate_obj_or_cam(data, ROTATE_SPEED, Y_AXIS);
        rotated = 1;
    }
    if (move->rotate_up) {
        rotate_obj_or_cam(data, -ROTATE_SPEED, X_AXIS);
        rotated = 1;
    }
    if (move->rotate_down) {
        rotate_obj_or_cam(data, ROTATE_SPEED, X_AXIS);
        rotated = 1;
    }

    return rotated;
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



// t_vec3 cam_axis_x(t_cam *cam)
// {
//     t_vec3 forward;
//     t_vec3 world_up;
//     t_vec3 right;

//     forward = cam_axis_z(cam);
//     world_up = new_vector(0, 1, 0);
//     right = vector_cross(world_up, forward);

//     if(vector_magnitude(right) < 0.001f)
//         right = new_vector(1, 0, 0);
//     else
//         right = vector_normalize(right);
//     return (right);
// }




// add translate light
/*
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
*/


/*
// void	rotate_objects(t_olist *node, float angle, t_axis axis)
// {
// 	t_shape	*obj;

// 	if (!node || !node->shape)
// 		return ;
// 	obj = node->shape;
// 	if (obj->obj_type == PL || obj->obj_type == CY)
// 	{
// 		if (axis == Y_AXIS)
// 			obj->normal.direction = vector_normalize(rotate_y(obj->normal.direction,
// 						angle));
// 		else
// 			obj->normal.direction = vector_normalize(rotate_x(obj->normal.direction,
// 						angle));
// 	}
// }

*/







// light cannot be rotated
// int	handle_rotation(t_data *data)
// {
// 	t_move_state	*move;

// 	if (!data)
// 		return (0);
// 	move = data->move_state;
// 	if (is_exeption(data, NO_ROT))
// 		return (0);
// 	if (move->rotate_left)
// 	{
// 		rotate_obj_or_cam(data, -ROTATE_SPEED, Y_AXIS);
// 		printf("pressed left\n");
// 		print_cam_pos(data->scene);
// 	}

// 	if (move->rotate_right)
// 	{
// 		rotate_obj_or_cam(data, ROTATE_SPEED, Y_AXIS);
// 		printf("pressed right\n");
// 	}
// 	if (move->rotate_up)
// 		rotate_obj_or_cam(data, -ROTATE_SPEED, X_AXIS);
// 	if (move->rotate_down)
// 		rotate_obj_or_cam(data, ROTATE_SPEED, X_AXIS);
// 	return (move->rotate_left || move->rotate_right || move->rotate_up
// 		|| move->rotate_down);
// }

// // need to add light
// void	rotate_obj_or_cam(t_data *data, float angle, t_axis axis)
// {
// 	if (data->control_cam)
// 		rotate_cam(&data->scene->cam, angle, axis);
// 	else if (data->scene->obj_selected)
// 		rotate_objects(data->scene->obj_selected, angle, axis);
// }



// t_vec3	rotate_y(t_vec3 current, float angle)
// {
// 	t_vec3	rotated;
// 	float	cosinus;
// 	float	sinus;

// 	cosinus = cosf(angle);
// 	sinus = sinf(angle);
// 	rotated.x = current.x * cosinus + current.z * sinus;
// 	rotated.y = current.y;
// 	rotated.z = -current.x * sinus + current.z * cosinus;
// 	rotated.w = current.w;
// 	return (rotated);
// }

// t_vec3	rotate_x(t_vec3 current, float angle)
// {
// 	t_vec3	rotated;
// 	float	cosinus;
// 	float	sinus;

// 	cosinus = cosf(angle);
// 	sinus = sinf(angle);
// 	rotated.x = current.x;
// 	rotated.y = current.y * cosinus - current.z * sinus;
// 	rotated.z = current.y * sinus + current.z * cosinus;
// 	rotated.w = current.w;
// 	return (rotated);
// }


// void	rotate_cam(t_cam *cam, float angle, t_axis axis)
// {
// 	if (axis == Y_AXIS)
// 	{
// 		cam->orient.direction = vector_normalize(rotate_y(cam->orient.direction,
// 					angle));
// 		printf("Y AXS\n");
// 	}

// 	else if (axis == X_AXIS)
// 	{
// 		cam->orient.direction = vector_normalize(rotate_x(cam->orient.direction,
// 					angle));
// 		printf("X AXES");
// 	}
// 	setup_camera_angle(cam);
// }


// void rotate_cam_local(t_cam *cam, float angle, t_vec3 axis)
// {
//     cam->orient.direction = vector_normalize(
//         rotate_around_axis(cam->orient.direction, axis, angle)
//     );
// }


// void rotate_obj_or_cam(t_data *data, float angle, t_axis axis)
// {
//     if (data->control_cam)
//     {
//         t_cam *cam = &data->scene->cam;
//         t_vec3 right = cam_axis_x(cam);
//         t_vec3 up = cam_axis_y(cam);

//         if (axis == Y_AXIS)
//             rotate_cam_local(cam, angle, up);       // LEFT/RIGHT
//         else if (axis == X_AXIS)
//             rotate_cam_local(cam, angle, right);    // UP/DOWN
//     }
//     else if (data->scene->obj_selected)
//         rotate_object_local(data->scene->obj_selected->shape, angle, axis);
// }


// t_vec3 cam_axis_z(t_cam *cam)
// {
//     return (vector_normalize(cam->orient.direction));
// }


// t_vec3 cam_axis_x(t_cam *cam)
// {
//     t_vec3 forward;
//     t_vec3 world_up;
//     t_vec3 right;

//     forward = cam_axis_z(cam);
//     world_up = new_vector(0, 1, 0);

//     if (fabsf(vector_dot(forward, world_up)) > 0.999f)
//         world_up = new_vector(0, 0, 1);

//     right = vector_cross(world_up, forward);
//     right = vector_normalize(right);

//     return (right);
// }


// t_vec3 cam_axis_y(t_cam *cam)
// {
//     t_vec3 forward;
//     t_vec3 right;

//     forward = cam_axis_z(cam);
//     right = cam_axis_x(cam);
//     return (vector_normalize(vector_cross(forward, right)));
// }