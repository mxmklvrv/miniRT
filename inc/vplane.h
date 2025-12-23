#ifndef VPLANE_H
# define VPLANE_H

#include "scene.h"
typedef struct s_vplane
{
	float	width;
	float	height;
	float	x_pixel;
	float	y_pixel;

}			t_vplane;

t_vplane	*get_view_plane(float width, float height, float fov);
void		rt(void *mlx, void *window, t_scene *scene);

#endif