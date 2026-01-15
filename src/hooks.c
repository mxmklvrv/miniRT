#include "minirt.h"

 static int	key_exit_hook(int key, t_data *data);

 void	set_hooks(t_data *data)
 {
 	mlx_key_hook(data->win, key_exit_hook, data);
 	mlx_hook(data->win, ON_DESTROY, 0, mlx_loop_end, data->mlx);
 }

 static int	key_exit_hook(int key, t_data *data)
 {
 	if (key == ESCAPE)
 		mlx_loop_end(data->mlx);
 	return (EXIT_SUCCESS);
 }

 void	redraw_scene(t_data *data, t_scene *scene)
{
	ft_bzero(data->addr, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
	draw_scene(data, scene);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
