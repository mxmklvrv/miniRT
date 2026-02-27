#include "minirt.h"

static int	get_pixels_to_render(int render_cycles);
static void	draw_one_render_cycle(t_data *data, int pixels_to_render);
static void	fill_pixels_for_cycle(t_data *data, t_pixel pixel, int pixels_to_render);

void	draw_scene(t_data *data)
{
	int		render_cycle;
	int		pixels_to_render;

	setup_scene(data->scene);
	render_cycle = 5;
	pixels_to_render = get_pixels_to_render(render_cycle);
	while (render_cycle > 0)
	{
		draw_one_render_cycle(data, render_cycle);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		pixels_to_render /= 2;
		render_cycle--;
		printf("Cycle: %i\n", render_cycle);
	}
	printf("Finished\n");
}

static void	draw_one_render_cycle(t_data *data, int pixels_to_render)
{
	t_pixel	pixel;
	t_ray	ray;

	ray.origin = data->scene->cam.orient.origin;
	pixel.j = 0;
	while (pixel.j < HEIGHT)//TODO: add multi threading
	{
		pixel.i = 0;
		while (pixel.i < WIDTH)
		{
			ray.direction = get_direction_for_position(pixel, data->scene->cam);
			pixel.color = trace_color(ray, data->scene);
			fill_pixels_for_cycle(data, pixel, pixels_to_render);
			pixel.i += pixels_to_render;
		}
		pixel.j += pixels_to_render;
	}
}

static int	get_pixels_to_render(int render_cycles)
{
	int	res;

	res = 1;
	while (render_cycles > 1)
	{
		res *= 2;
		render_cycles--;
	}
	return (res);
}

static void	fill_pixels_for_cycle(t_data *data, t_pixel pixel, int pixels_to_render)
{
	int	max_i;
	int	max_j;
	int	start_i;

	max_i = pixel.i + pixels_to_render;
	max_j = pixel.j + pixels_to_render;
	start_i = pixel.i;
	while (pixel.j <= max_j && pixel.j < HEIGHT)
	{
		pixel.i = start_i;
		while (pixel.i <= max_i && pixel.i < WIDTH)
		{
			ft_mlx_put_pixel(data, pixel);//TODO: add writting to ppm(?)
			pixel.i++;
		}
		pixel.j++;
	}
}

