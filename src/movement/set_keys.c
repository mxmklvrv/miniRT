#include "minirt.h"

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
/*
// new for multiple lights
void	set_general_keys(int key, t_data *data)
{
	if (key == KEY_TAB)
	{
		if (data->control_light)
			select_light(data->scene);
		else if (data->control_cam)
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
// new for multiple lights up
*/

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