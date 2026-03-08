#include "minirt.h"

// TODO: probably after parsing
/**
 * 1. scene lvl validation:
 * -1 cam 1 amb 1 light
 * - at list 1 object probably
 * 2. obj lvl validation:
 *
//////////////////////////////////////////////////////////////////////////////////////////////////

*/

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
    print_scene(&scene);   // Test PRINT
	if (!visuals_loop(&scene))
	{
		free_scene(&scene);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	init_scene(t_scene *scene)
{
	scene->qt_ambiant = 0;
	scene->qt_cam = 0;
	scene->qt_light = 0;
    scene->next_obj_id = 0; // added
	scene->err_m = NULL;
	scene->obj_list = NULL;
	scene->obj_selected = NULL;
}



void	print_scene(t_scene *scene)
{
	t_olist	*tmp;

	printf("\n---- SCENE DEBUG ----\n");

	printf("Ambient count: %d\n", scene->qt_ambiant);
	printf("Camera count : %d\n", scene->qt_cam);
	printf("Light count  : %d\n", scene->qt_light);

	printf("\nCamera:\n");
	printf("  pos: %.2f %.2f %.2f\n",
		scene->cam.orient.origin.x,
		scene->cam.orient.origin.y,
		scene->cam.orient.origin.z);

	printf("  dir: %.2f %.2f %.2f\n",
		scene->cam.orient.direction.x,
		scene->cam.orient.direction.y,
		scene->cam.orient.direction.z);

	printf("  fov: %.2f\n", scene->cam.fov);

	printf("\nLight:\n");
	printf("  pos: %.2f %.2f %.2f\n",
		scene->light.pos.x,
		scene->light.pos.y,
		scene->light.pos.z);

	printf("  brightness: %.2f\n", scene->light.bright);

	printf("\nObjects:\n");

	tmp = scene->obj_list;
	while (tmp)
	{
		t_shape *s = tmp->shape;

		printf("\nObject ID: %d\n", s->obj_id);
		printf("Type: %d\n", s->obj_type);

		if (s->obj_type == SP)
		{
			printf("Sphere center: %.2f %.2f %.2f\n",
				s->center.x, s->center.y, s->center.z);
			printf("Diameter: %.2f\n", s->diameter);
		}

		if (s->obj_type == PL)
		{
			printf("Plane point: %.2f %.2f %.2f\n",
				s->normal.origin.x,
				s->normal.origin.y,
				s->normal.origin.z);

			printf("Normal: %.2f %.2f %.2f\n",
				s->normal.direction.x,
				s->normal.direction.y,
				s->normal.direction.z);
		}

		if (s->obj_type == CY)
		{
			printf("Cylinder center: %.2f %.2f %.2f\n",
				s->normal.origin.x,
				s->normal.origin.y,
				s->normal.origin.z);

			printf("Axis: %.2f %.2f %.2f\n",
				s->normal.direction.x,
				s->normal.direction.y,
				s->normal.direction.z);

			printf("Diameter: %.2f\n", s->diameter);
			printf("Height: %.2f\n", s->height);
		}

		printf("Color: %d\n", s->colour);

		tmp = tmp->next;
	}

	printf("\n---------------------\n");
}