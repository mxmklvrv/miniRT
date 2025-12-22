#include "minirt.h"

t_camera	*cam_new(t_vec3 *origin, t_vec3 *dir, float fov)
{
	t_camera *cam;

	cam = malloc(sizeof(t_camera));
	if (!cam)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	cam->dir = dir;
	cam->origin = origin;
	cam->fov = fov;

	return (cam);
}