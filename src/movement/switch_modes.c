#include "minirt.h"

void	switch_to_obj(t_data *data)
{
	data->control_cam = 0;
	data->control_light = 0;
	print_pos(data->scene);
}

void	toggle_cam(t_data *data)
{
	data->control_cam = !data->control_cam;
	data->control_light = 0;
	if (data->control_cam)
		print_cam_light_pos(data);
	else
		print_pos(data->scene);
}

void	toggle_light(t_data *data)
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

void	select_light(t_data *data)
{
	if (!data->scene->light_selected)
		data->scene->light_selected = data->scene->light_list;
	else if (data->scene->light_selected->next)
		data->scene->light_selected = data->scene->light_selected->next;
	else
		data->scene->light_selected = data->scene->light_list;
	print_cam_light_pos(data);
}
