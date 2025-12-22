#ifndef SCENE_H
# define SCENE_H

#include "camera.h"
#include "sphere.h"
typedef struct s_scene
{
	t_camera	*cam;
	t_sphere *sp; // later pointer to all figs
	float		width;
	float		height;

}				t_scene;

t_scene			*scene_new(t_camera *cam, t_sphere *sp);

#endif