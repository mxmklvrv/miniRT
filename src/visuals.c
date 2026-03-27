#include "minirt.h"

static bool	set_controls(t_data *data, t_scene *scene);

bool	visuals_loop(t_scene *scene)
{
	t_data	data;

	if (!set_visuals(&data))
		return (false);
	if (!set_controls(&data, scene))
		return (false);
	set_hooks(&data);
	draw_scene(&data); // show scene here
	// mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	free_visuals(&data);
	return (true);
}

bool	set_visuals(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (false);
	data->img = NULL;
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
	{
		free_visuals(data);
		return (false);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		free_visuals(data);
		return (false);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (true);
}
static bool	set_controls(t_data *data, t_scene *scene)
{
	data->scene = scene;
	data->move_state = ft_calloc(1, sizeof(t_move_state));
	if (!data->move_state)
	{
		error_msg(ERR_ALLOC, NULL);
		free_visuals(data);
		return (false);
	}
	data->control_cam = 0;
	data->control_light = 0;
	data->scene->obj_selected = data->scene->obj_list;
	return (true);
}

void	free_visuals(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->move_state)
		free(data->move_state);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	ft_mlx_put_pixel(t_data *data, t_pixel pixel)
{
	char	*dst;

	if (pixel.i >= 0 && pixel.i < WIDTH && pixel.j >= 0 && pixel.j < HEIGHT)
	{
		dst = data->addr + (pixel.j * data->line_length + pixel.i
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = pixel.color;
	}
}
