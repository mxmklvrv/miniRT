#include "minirt.h"

static void	setup_camera_angle(t_cam *cam);
static void	setup_object_matrix(t_olist *obj_list);

void	setup_scene(t_scene *scene)
{
	setup_camera_angle(&scene->cam);
	setup_object_matrix(scene->obj_list);
}

/*
 * Calculates pixel size relative to 3d world depending on camera fov.
 * Distance between camera and 2d screen is assumed to be 1.
 */
static void	setup_camera_angle(t_cam *cam)
{
	cam->pixel_size = 1 * tanf(degrees_to_radians(cam->fov / 2)) * 2
		/ ft_max(2, WIDTH, HEIGHT);
	//cam->matrix = ;
	//t_vec3	opposite_cam;
	//const t_vec3	up_view = new_vector(0, 0, 1);

	//cam->orient.direction = vector_normalize(cam->orient.direction);
	//opposite_cam = vector_multiply(cam->orient.direction, -1);
	//cam->vector_i = vector_cross(opposite_cam,up_view);
	//cam->vector_j = vector_cross(opposite_cam, cam->vector_i);
}

static void	setup_object_matrix(t_olist *obj_list)
{
	t_matrix	scaling;

	while (obj_list)
	{
		//scaling = 
		set_matrix(&obj_list->shape->matrix, new_scaling_matrix(0.5, 1, 1));
		obj_list = obj_list->next;
	}
}

void	set_matrix(t_matrix *old_m, t_matrix new_m)
{
	free_matrix(*old_m);
	*old_m = new_m;
}

