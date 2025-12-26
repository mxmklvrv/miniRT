#include "minirt.h"

// int	main(int argc, char **argv)
// {
// 	char	*format;

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



