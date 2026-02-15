#include "minirt.h"

/**
 * TODO:
 * get current node (sphere, plane cylinder)
 * check type
 * cast to correct struct
 * make changes
 */

/**
 * added to scene struct *obj_selected
 * initialized in init scene to null
 * to track selected object

	* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!somewhere after parsing need to do:

	* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!scene->obj_selected = scene->obj_list
 *
 *
 */

/**
 * If there is next obj - select it
 * Otherwise select the first one
 */
void	select_object(t_scene *scene)
{
	if (!scene->obj_selected)
		return ;
	if (scene->obj_selected->next)
		scene->obj_selected = scene->obj_selected->next;
	else
		scene->obj_selected = scene->obj_list;
}

// need to create move bector with new_vec
void	translate_object(t_olist *node, t_vec3 move_vec)
{
	t_sp	*sp;
	t_pl	*pl;
	t_cy	*cy;

	if (!node)
		return ;
	if (node->obj_type == SP)
	{
		sp = (t_sp *)node->obj;
		sp->sp_center = vector_add(sp->sp_center, move_vec);
	}
	else if (node->obj_type == PL)
	{
		pl = (t_pl *)node->obj;
		pl->normal.origin = vector_add(pl->normal.origin, move_vec);
	}
	else if (node->obj_type == CY)
	{
		cy = (t_cy *)node->obj;
		cy->normal.origin = vector_add(cy->normal.origin, move_vec);
	}
}

void	handle_movement(int key, t_scene *scene)
{
	t_vec3	move_vec;

	move_vec = new_vector(0, 0, 0);
	if (key == XK_w || key == XK_W) // key w
		move_vec.z -= 1;
	if (key == XK_s || key == XK_S) // key s
		move_vec.z += 1;
	if (key == XK_a || key == XK_A) // a
		move_vec.x -= 1;
	if (key == XK_d || key == XK_D) // d
		move_vec.x += 1;
	if (key == XK_q || key == XK_Q) // q
		move_vec.y += 1;
	if (key == XK_e || key == XK_E) // e
		move_vec.y -= 1;
	translate_object(scene->obj_selected, move_vec);
}

// not sure about resizing
void	resize_objects(t_olist *node, float value)
{
	t_sp	*sp;
	t_cy	*cy;

	if (!node)
		return ;
	if (node->obj_type == SP)
	{
		sp = (t_sp *)node->obj;
		sp->diameter += value;
		if (sp->diameter < 0.1f)
			sp->diameter = 0.1f;
	}
	else if (node->obj_type == CY)
	{
		cy = (t_cy *)node->obj;
		cy->diameter += value;
		cy->height += value;
		if (cy->diameter < 0.1f)
			cy->diameter = 0.1f;
		if (cy->height < 0.1f)
			cy->height = 0.1f;
	}
}

void	rotate_objects(t_olist *node, float angle)
{
	t_pl	*pl;
	t_cy	*cy;

	if (!node)
		return ;
	if (node->obj_type == PL)
	{
		pl = (t_pl *)node->obj;
		pl->normal.direction = rotate_y(pl->normal.direction, angle);
	}
	else if (node->obj_type == CY)
	{
		cy = (t_cy *)node->obj;
		cy->normal.direction = rotate_y(cy->normal.direction, angle);
	}
}
t_vec3	rotate_y(t_vec3 current, float angle)
{
	t_vec3	rotated;
	float	cosinus;
	float	sinus;

	cosinus = cosf(angle);
	sinus = sinf(angle);
	rotated.x = current.x * cosinus + current.z * sinus;
	rotated.y = current.y;
	rotated.z = -current.x * sinus + current.z * cosinus;
	rotated.w = current.w;
}

// need rotation
// need camera movement