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
    user_manual();
	if (!visuals_loop(&scene))
	{
		free_scene(&scene);
		return (EXIT_FAILURE);
	}
	free_scene(&scene);
	return (EXIT_SUCCESS);
}

void	init_scene(t_scene *scene)
{
	scene->qt_ambiant = 0;
	scene->qt_cam = 0;
	scene->qt_light = 0;
    scene->next_obj_id = 1;
	scene->error_line = NULL;
	scene->obj_list = NULL;
	scene->obj_selected = NULL;
}

