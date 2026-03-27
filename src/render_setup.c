#include "minirt.h"

void			setup_camera_angle(t_cam *cam);
static float	degrees_to_radians(float degrees);
static void		setup_objects(t_olist *obj_list);

/* Setup camera angle and normalize object vectors before rendering.
 * @param	t_scene	*scene	pointer to t_scene scene.
 */
void setup_scene(t_scene *scene)
{
	setup_camera_angle(&scene->cam);
	setup_objects(scene->obj_list);
}

/*
 * Calculates pixel size relative to 3d world depending on camera fov.
 * Distance between camera and 2d screen is assumed to be 1.
 */

/*
void	setup_camera_angle(t_cam *cam)
{
	t_vec3 forward;
	t_vec3 world_up;

	cam->pixel_size = 1 * tanf(degrees_to_radians(cam->fov) / 2) * 2
		/ ft_max(2, WIDTH, HEIGHT);
	forward = vector_normalize(cam->orient.direction);
	world_up = new_vector(0, 1, 0);

	if (fabsf(vector_dot(forward, world_up)) > 0.999)
		world_up = new_vector(0, 0, 1);
	cam->right = vector_normalize(vector_cross(forward, world_up));
	cam->up = vector_cross(cam->right, forward);
	cam->orient.direction = forward;
	//cam->matrix = ;
	//t_vec3	opposite_cam;
	//const t_vec3	up_view = new_vector(0, 0, 1);

	//cam->orient.direction = vector_normalize(cam->orient.direction);
	//opposite_cam = vector_multiply(cam->orient.direction, -1);
	//cam->vector_i = vector_cross(opposite_cam,up_view);
	//cam->vector_j = vector_cross(opposite_cam, cam->vector_i);
}
*/
// calculates local axes (forward, right, up)
void setup_camera_angle(t_cam *cam)
{
	t_vec3 forward;
	t_vec3 right;
	t_vec3 up;

	cam->pixel_size = tanf(degrees_to_radians(cam->fov) / 2) * 2 / ft_max(2, WIDTH, HEIGHT);

	forward.x = cosf(cam->pitch) * sinf(cam->yaw);
	forward.y = sinf(cam->pitch);
	forward.z = cosf(cam->pitch) * cosf(cam->yaw);
	forward.w = 0;

	forward = vector_normalize(forward);
	right = vector_normalize(vector_cross(new_vector(0, 1, 0), forward));
	up = vector_cross(forward, right);

	cam->orient.direction = forward;
	cam->right = right;
	cam->up = up;
}

/* Normalizes vectors of objects if they have vectors (plane and cylinder).
 * @param	t_olist	*obj_list	pointer to t_olist of objects.
 */
 static void	setup_objects(t_olist *obj_list)
{
	t_olist	*obj;

	obj = obj_list;
	while (obj)
	{
		if (obj->shape->obj_type == PL || obj->shape->obj_type == CY)
			obj->shape->normal.direction =
				vector_normalize(obj->shape->normal.direction);
		obj = obj->next;
	}
 }

 /* Converts degrees to radians.
 * @param	float	degrees	degrees of angle;
 * @returns	float	angle in radians.
 */
static float degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180);
}
