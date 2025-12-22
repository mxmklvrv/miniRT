#ifndef CAMERA_H
# define CAMERA_H

#include "vector.h"
typedef struct s_camera
{
	t_vec3	*origin;
	t_vec3	*dir;
	float	fov;
}			t_camera;

t_camera	*cam_new(t_vec3 *origin, t_vec3 *dir, float fov);


#endif