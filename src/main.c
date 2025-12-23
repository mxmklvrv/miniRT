#include "minirt.h"

// int	main(int argc, char **argv)
// {
// 	char *format;

// 	if (!check_args(argc, argv, &format))
// 		return (handle_error());
// 	if (!visuals_loop(&format))
// 		return (handle_error());
// 	return (EXIT_SUCCESS);
// }

// bool	check_args(int argc, char **argv, char **format)
// {
// 	(void)argc;
// 	(void)argv;
// 	*format = ft_strdup("Hello world!");
// 	if (*format == NULL)
// 		return (false);
// 	return (true);
// }

// int	handle_error(void)
// {
// 	ft_putendl_fd(ERR_MSG, STDERR_FILENO);
// 	return (EXIT_FAILURE);
// }

// bool	visuals_loop(char **format)
// {
// 	t_vars	vars;
// 	t_data	data;

// 	if (!set_visuals(&vars, &data))
// 	{
// 		free_format(format);
// 		return (false);
// 	}
// 	set_hooks(&vars);
// 	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
// 	mlx_loop(vars.mlx);
// 	free_visuals(&vars, &data);
// 	free_format(format);
// 	return (true);
// }

// void	free_format(char **format)
// {
// 	if (*format != NULL)
// 		free(*format);
// }

int	main(void)
{
	void		*mlx;
	void		*window;
	t_vec3		*sphere_center;
	t_sphere	*sphere;
	t_vec3		*cam_origin;
	t_vec3		*cam_dir;
	t_camera	*cam;
	t_scene		*scene;

	mlx = mlx_init();
	sphere_center = vec_new(3, 2, -32);
	sphere = sphere_new(sphere_center, 12.6 / 2);
	cam_origin = vec_new(0, 0, 0);
	cam_dir = vec_new(0, 0, -1);
	cam = cam_new(cam_origin, cam_dir, 110);
	scene = scene_new(cam, sphere);
	scene->width = 800;
	scene->height = 600;
	window = mlx_new_window(mlx, scene->width, scene->height, "YOLO");
	rt(mlx, window, scene);
	mlx_loop(mlx);
}
