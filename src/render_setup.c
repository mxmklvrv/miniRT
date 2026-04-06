/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:41:13 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:41:14 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	setup_objects(t_olist *obj_list);

/* Setup camera angle and normalize object vectors before rendering.
 * @param	t_scene	*scene	pointer to t_scene scene.
 */
void	setup_scene(t_scene *scene)
{
	setup_camera_angle(&scene->cam);
	setup_objects(scene->obj_list);
}

/* Calculates local axes (forward, right, up) */
void	setup_camera_angle(t_cam *cam)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	cam->pixel_size = tanf(degrees_to_radians(cam->fov) / 2) * 2
		/ ft_max(2, WIDTH, HEIGHT);
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
			obj->shape->normal.direction = vector_normalize(
					obj->shape->normal.direction);
		obj = obj->next;
	}
}
