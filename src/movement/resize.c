
#include "minirt.h"

int	handle_resize(t_data *data)
{
	t_move_state	*move;

	if (!data->scene)
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
		obj->radius += value;
		if (obj->radius < 0.1f)
			obj->radius = 0.1f;
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
	obj->half_height += value;
	if (obj->half_height < 0.1f)
		obj->half_height = 0.1f;
	return (1);
}
