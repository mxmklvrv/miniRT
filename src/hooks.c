#include "minirt.h"

//  static int	key_exit_hook(int key, t_data *data);

//  void	set_hooks(t_data *data)
//  {
//  	// mlx_key_hook(data->win, key_exit_hook, data);
//  	// mlx_hook(data->win, ON_DESTROY, 0, mlx_loop_end, data->mlx);
// 	// check if malloc fails
// 	// probably will do that in init
// 	data->move_state = ft_calloc(1, sizeof(t_move_state));
// 	data->control_cam = 0;
// 	data->scene->obj_selected = data->scene->obj_list;
// 	mlx_hook(data->win, 2, 1L << 0, key_press_hook, data);
// 	mlx_hook(data->win, 3, 1L << 1, key_release_hook, data);
// 	mlx_loop_hook(data->mlx, render_hook, data);
//  }

// // on release
void	set_hooks(t_data *data)
 {
	data->control_cam = 0;
	mlx_hook(data->win, 2, 1L << 0, key_press_hook, data);
	mlx_hook(data->win, 3, 1L << 1, key_release_hook, data);
 }



//  static int	key_exit_hook(int key, t_data *data)
//  {
//  	if (key == ESCAPE)
//  		mlx_loop_end(data->mlx);
//  	return (EXIT_SUCCESS);
//  }

 void	redraw_scene(t_data *data, t_scene *scene)
{
	ft_bzero(data->addr, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
	draw_scene(data, scene);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

