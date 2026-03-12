#include "minirt.h"

//  static int	key_exit_hook(int key, t_data *data);

void	set_hooks(t_data *data)
{
	// mlx_key_hook(data->win, key_exit_hook, data);
	// check if malloc fails
	// probably will do that in init
	data->move_state = ft_calloc(1, sizeof(t_move_state));
	if (!data->move_state)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		mlx_loop_end(data->mlx);
		return ;
	}
	data->control_cam = 0;
	data->scene->obj_selected = data->scene->obj_list;
	data->scene->cam.yaw = atan2f(data->scene->cam.orient.direction.x,
			data->scene->cam.orient.direction.z);
	data->scene->cam.pitch = asinf(data->scene->cam.orient.direction.y);
	mlx_hook(data->win, ON_PRESS, 1L << 0, key_press_hook, data);
	mlx_hook(data->win, ON_RELEASE, 1L << 1, key_release_hook, data);
	mlx_hook(data->win, ON_DESTROY, 0, mlx_loop_end, data->mlx);
	mlx_loop_hook(data->mlx, render_hook, data);
}

// // on release

// void	set_hooks(t_data *data)
// {
// 	data->control_cam = 0;
// 	data->scene->obj_selected = data->scene->obj_list;
// 	mlx_hook(data->win, ON_PRESS, 1L << 0, key_press_hook, data);
// 	mlx_hook(data->win, ON_RELEASE, 1L << 1, key_release_hook, data);
// 	mlx_hook(data->win, ON_DESTROY, 0, mlx_loop_end, data->mlx);
// }

void	redraw_scene(t_data *data)
{
	// ft_bzero(data->addr, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
	// mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	if (data->control_cam)
		setup_camera_angle(&data->scene->cam);
	draw_scene(data);
	// mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
