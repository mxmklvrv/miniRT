#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (confirm_input(argc, argv) == 1)
		return (EXIT_FAILURE);
	init_scene(&scene);
	if (parse_input_file(argv[1], &scene) == 1)
	{
		free_scene(&scene);
		return (EXIT_FAILURE);
	}
	if (!visuals_loop(&scene))
	{
		free_scene(&scene);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	init_scene(t_scene *scene)
{
	scene->obj_list = NULL;
	scene->obj_selected = NULL;
	scene->qt_ambiant = 0;
	scene->qt_cam = 0;
	scene->qt_light = 0;
	scene->err_m = NULL;
}