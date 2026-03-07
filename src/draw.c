#include "minirt.h"

static int		get_pixels_to_render(int render_cycles);
static void		draw_one_render_cycle(t_data *data, int pixels_to_render, bool *first_cycle);
static t_vec3	get_direction_for_position(t_pixel pixel, t_cam cam);
static void		fill_pixels_for_cycle(t_data *data, t_pixel pixel, int pixels_to_render, bool *first_cycle);

void	draw_scene(t_data *data)
{
	const int	render_cycle = 5;
	int			pixels_to_render;
	bool		first_cycle;

	setup_scene(data->scene);
	pixels_to_render = get_pixels_to_render(render_cycle);
	first_cycle = true;
	while (1)
	{
		draw_one_render_cycle(data, pixels_to_render, &first_cycle);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		printf("Pixels rendered: %i\n", pixels_to_render);
		if (pixels_to_render == 1)
			break ;
		pixels_to_render /= 2;
	}
	printf("Finished\n");
}

static void	draw_one_render_cycle(t_data *data, int pixels_to_render, bool *first_cycle)
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
			fill_pixels_for_cycle(data, pixel, pixels_to_render, first_cycle);
			pixel.i += pixels_to_render;
		}
		pixel.j += pixels_to_render;
	}
}

/*
 * Returns normalized vector from camera origin to pixel in 3d coordinates
 */
static t_vec3	get_direction_for_position(t_pixel pixel, t_cam cam)
{
	t_vec3		direction;
	t_matrix	rotation_i;
	t_matrix	rotation_j;
	t_matrix	rotation;
	float		angle;

	angle = -atanf((pixel.i - WIDTH / 2) * cam.pixel_size);
	rotation_i = new_rotation_z_matrix(angle);
	angle = atanf((pixel.j - HEIGHT / 2) * cam.pixel_size);
	rotation_j = new_rotation_x_matrix(angle);
	rotation = chain_matrices(rotation_i, rotation_j);
	direction = matrix_multiply_by_vector(rotation, cam.orient.direction);
	free_matrix(rotation);
	//direction = vector_normalize(direction);
	return (direction);
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

static void	fill_pixels_for_cycle(t_data *data, t_pixel pixel, int pixels_to_render, bool *first_cycle)
{
	int	max_i;
	int	max_j;
	int	start_i;

	max_i = pixel.i + pixels_to_render;
	max_j = pixel.j + pixels_to_render;
	start_i = pixel.i;
	pixels_to_render *= 2;
	while (pixel.j <= max_j && pixel.j < HEIGHT)
	{
		pixel.i = start_i;
		if (*first_cycle)
			*first_cycle = false;
		else if (pixel.i % pixels_to_render == 0 && pixel.j % pixels_to_render == 0)
			pixel.i++;
		while (pixel.i <= max_i && pixel.i < WIDTH)
		{
			ft_mlx_put_pixel(data, pixel);//TODO: add writting to ppm(?)
			pixel.i++;
		}
		pixel.j++;
	}
}
