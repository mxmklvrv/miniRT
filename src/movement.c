#include "minirt.h"

#define MOVE_SPEED 0.5f
#define ROTATE_SPEED 0.1f
#define RESIZE_SPEED 0.2f

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_Q 113
#define KEY_E 101
#define KEY_C 99
#define KEY_SPACE 32
#define KEY_TAB 65289
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_PLUS 61
#define KEY_MINUS 45
#define KEY_ESC 65307

typedef struct s_move_state
{
	int	forward;
	int	backward;
	int	left;
	int	right;
	int	up;
	int	down;
	int	rotate_left;
	int	rotate_right;
	int	resize_up;
	int	resize_down;
}		t_move_state;

int	key_press_hook(int key, t_data *data)
{
	t_move_state	*move;

	move = data->move_state;
	if (key == KEY_TAB)
		select_object(data->scene);
	// for camcontrol here needed
	else if (key == KEY_W)
		move->forward = 1;
	else if (key == KEY_S)
		move->backward = 1;
	else if (key == KEY_A)
		move->left = 1;
	else if (key == KEY_D)
		move->right = 1;
	else if (key == KEY_Q)
		move->up = 1;
	else if (key == KEY_E)
		move->down = 1;
	// rotation
	else if (key == KEY_LEFT)
		move->rotate_left = 1;
	else if (key == KEY_RIGHT)
		move->rotate_right = 1;
	else if (key == KEY_PLUS)
		move->resize_up = 1;
	else if (key == KEY_MINUS)
		move->resize_down = 1;
	else if (key == KEY_ESC)
		mlx_loop_end(data->mlx);
	return (0);
}

int	key_release_hook(int key, t_data *data)
{
	t_move_state	*move;

	move = data->move_state;
	if (key == KEY_TAB)
		select_object(data->scene);
	// for camcontrol here needed
	else if (key == KEY_W)
		move->forward = 0;
	else if (key == KEY_S)
		move->backward = 0;
	else if (key == KEY_A)
		move->left = 0;
	else if (key == KEY_D)
		move->right = 0;
	else if (key == KEY_Q)
		move->up = 0;
	else if (key == KEY_E)
		move->down = 0;
	// rotation
	else if (key == KEY_LEFT)
		move->rotate_left = 0;
	else if (key == KEY_RIGHT)
		move->rotate_right = 0;
	else if (key == KEY_PLUS)
		move->resize_up = 0;
	else if (key == KEY_MINUS)
		move->resize_down = 0;
	return (0);
}

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
 *s_data added from Anya's brunch and added
	t_scene *scene;
	void	*move_state;
	int		control_cam;

	move state struct to check press release buttons

 */

/**
 * If there is next obj - select it
 * Otherwise select the first one
 */
void	select_object(t_scene *scene)
{
	if (!scene->obj_selected)
		scene->obj_selected = scene->obj_list;
	else if (scene->obj_selected->next)
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
	return (rotated);
}



	// need camera movement