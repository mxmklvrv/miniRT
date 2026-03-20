#include "minirt.h"

void setup_camera_angle(t_cam *cam);
// static void	setup_objects(t_olist *obj_list);
// static void	setup_object_matrix(t_shape *shape);

void setup_scene(t_scene *scene)
{
    setup_camera_angle(&scene->cam);
    // setup_objects(scene->obj_list);
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

float degrees_to_radians(float degrees)
{
    return (degrees * M_PI / 180);
}

// static void	setup_objects(t_olist *obj_list)
//{
//	while (obj_list)
//	{
//		setup_object_matrix(obj_list->shape);
//		obj_list = obj_list->next;
//	}
// }

// static void	setup_object_matrix(t_shape *shape)
//{
//	t_matrix	scaling;
//	//t_matrix	rotation;
//	t_matrix	translate;
//	t_matrix	inverse;
//	t_matrix	chain;
//	float		scale;

//	scale = shape->diameter / 2;
//	scaling = new_scaling_matrix(scale, scale, scale);
//	//rotation = new_rotation_matrix(shape->normal.direction);
//	if (shape->obj_type == SP)
//		translate = new_translation_matrix_vec3(shape->center);
//	else if (shape->obj_type == PL || shape->obj_type == CY)
//		translate = new_translation_matrix_vec3(shape->normal.origin);
//	else
//		return ;
//	chain = chain_matrices(translate, scaling);
//	inverse = new_inverse_matrix(chain);
//	free_matrix(chain);
//	set_matrix(&shape->matrix, inverse);
//}

void set_matrix(t_matrix *old_m, t_matrix new_m)
{
    free_matrix(*old_m);
    *old_m = new_m;
}
