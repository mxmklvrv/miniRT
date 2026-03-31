#include "minirt.h"



/*
// new functions for multiple lights down
void    select_light(t_scene *scene)
{
    if(!scene->light_selected)
        scene->light_selected = scene->light_list;
    else if (scene->light_selected->next)
        scene->light_selected = scene->light_selected->next;
    else
        scene->light_selected = scene->light_list;
}

void translate_light(t_llist *node, t_vec3 move_vec) // new for multiple lights
{
    if(!node || !node->light)
        return ;
    node->light->pos = vector_add(node->light->pos, move_vec);
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
		else if (data->control_light && data->scene->light_selected)
            translate_light(data->scene->light_selected, move_vec);
		else if (data->scene->obj_selected)
			translate_object(data->scene->obj_selected, move_vec);
		return (1);
	}
	return (0);
}
*/
// new functions up

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


void	update_cy_geo(t_shape *cy)
{
	if (!cy || cy->obj_type != CY)
		return ;
	cy->radius = cy->diameter / 2.0f;
	cy->half_h = cy->height / 2.0f;
}