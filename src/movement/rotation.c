#include "minirt.h"

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
			obj->normal.direction = vector_normalize(
				rotate_z(obj->normal.direction, angle));
		else
			obj->normal.direction = vector_normalize(
				rotate_x(obj->normal.direction, angle));
	}
}
