#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (confirm_input(argc, argv) == 1)
		return (EXIT_FAILURE);
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
