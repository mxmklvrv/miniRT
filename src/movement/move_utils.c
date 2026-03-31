#include "minirt.h"

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

void	obj_light_move_calculation(t_vec3 *move_vec, t_move_state *move)
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