#include "minirt.h"

t_scene	*scene_new(t_camera *cam, t_sphere *sp)
{
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	scene->cam = cam;
	scene->sp = sp;
	scene->height = 0;
	scene->width = 0;

	return (scene);
}