#include "minirt.h"

void	rt(void *mlx, void *window, t_scene *scene)
{
	int mlx_x; // for mlx_pixel_put
	int mlx_y = 0; // for mlx_pixel_put
	// need to put in buffer, then to window
	// for now straight to window
	float x_angle;
	float y_angle;
	int color; // for now, if we intersect with sphere -> white, black otherwise.
	t_vec3 *ray; // ray which we launch from cam
	t_vplane *vplane;  // okno prosmotra 
	float y_ray; // coord of ray
	float x_ray; // coord of ray

	vplane = get_view_plane(scene->width, scene->height, scene->cam->fov);
	y_angle = scene->height / 2;
	while(y_angle >= (scene->height /2) * (-1))
	{
		y_ray = y_angle * vplane->y_pixel;
		x_angle = (scene->width / 2) * (-1);
		mlx_x = 0;
		while(x_angle <= scene->width /2)
		{
			x_ray = x_angle * vplane->x_pixel;
			ray = vec_new(x_ray, y_ray, -1);
			vec_norm(ray);
			if(sphere_intersect(scene->cam, ray, scene->sp))
				color = 16777215;
			else
				color = 0;
			mlx_pixel_put(mlx, window, mlx_x, mlx_y, color);
			free(ray);
			x_angle++;
			mlx_x++;
		}
		y_angle--;
		mlx_y++;
	}
}

t_vplane *get_view_plane(float width, float height, float fov)
{
	t_vplane	*vplane;
	float aspect_ratio;

	vplane = malloc(sizeof(t_vplane));
	if(!vplane)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	aspect_ratio = width / height;
	vplane->width = tan(fov / 2 * (M_PI / 180));
	vplane->width *= 2;
	vplane->height = vplane->width / aspect_ratio;
	vplane->x_pixel = vplane->width / width;
	vplane->y_pixel = vplane->height / height;
	return (vplane);
}
