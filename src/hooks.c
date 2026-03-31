#include "minirt.h"

//  static int	key_exit_hook(int key, t_data *data);

void set_hooks(t_data *data)
{
    print_pos(data->scene);
    mlx_hook(data->win, ON_PRESS, 1L << 0, key_press_hook, data);
    mlx_hook(data->win, ON_RELEASE, 1L << 1, key_release_hook, data);
    mlx_hook(data->win, ON_DESTROY, 0, mlx_loop_end, data->mlx);
    mlx_loop_hook(data->mlx, render_hook, data);
}

void redraw_scene(t_data *data)
{
    // ft_bzero(data->addr, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
    // mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    // if (data->control_cam)
    // 	setup_camera_angle(&data->scene->cam); // not sure if needed
    draw_scene(data);
    // mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

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