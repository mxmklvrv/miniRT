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
 *s_data added from Anya's brunch and added
	t_scene *scene;
	void	*move_state;
	int		control_cam;

	move state struct to check press release buttons

 */



// NEED TO ADD ROTATION X
// NEED TO ADD SEP BUTTON FOR DIAM INCR

// VERSION WITH CONTINUOUS MOVEMENT

#define MOVE_SPEED 0.5f
#define ROTATE_SPEED 0.1f
#define RESIZE_SPEED 0.2f

#define KEY_W 119 // forward
#define KEY_A 97 // left
#define KEY_S 115 // back
#define KEY_D 100 // right
#define KEY_Q 113 // up
#define KEY_E 101 // down
#define KEY_C 99 // cam
#define KEY_TAB 65289 // switch obj
#define KEY_LEFT 65361 // rotate left
#define KEY_RIGHT 65363 // rotate right
#define KEY_UP 65362 // rotate up
#define KEY_DOWN 65364 // rotate down
#define KEY_PLUS 61 // resize up
#define KEY_MINUS 45 // resize down
#define KEY_ESC 65307 // esc


// VERSION WITH ON RELEASE MOVEMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


void set_hooks(t_data *data)
{
    // need to remove movestate from data struct
    data->control_cam = 0;

    mlx_hook(data->win, 2, 1L<<0, key_press_hook, data);
    mlx_hook(data->win, 3, 1L<<1, key_release_hook, data);
    mlx_hook(data->win, 17, 0, mlx_loop_end, data->mlx);

}



int	key_press_hook(int key, t_data *data)
{

    if(key == KEY_C)
    {
        data->control_cam = !data->control_cam;
        printf("controling cam");
    }
    else if(key == KEY_TAB)
        select_object(data->scene);
	else if (key == KEY_ESC)
		mlx_loop_end(data->mlx);
	return (0);
}

int	key_release_hook(int key, t_data *data)
{
	t_vec3 move_vec;
    int need_redrow;

    move_vec = new_vector(0, 0, 0);
    int need_redrow = 0;

	if (key == KEY_W)
		move_vec.z -= MOVE_SPEED;
	else if (key == KEY_S)
		move_vec.z += MOVE_SPEED;
	else if (key == KEY_A)
		move_vec.x -= MOVE_SPEED;
	else if (key == KEY_D)
		move_vec.x += MOVE_SPEED;
	else if (key == KEY_Q)
		move_vec.y += MOVE_SPEED;
	else if (key == KEY_E)
		move_vec.y -= MOVE_SPEED;
    if(move_vec.x != 0 || move_vec.y != 0 || move_vec.z !=0)
    {
        if(data->control_cam)
            translate_cam(&data->scene->cam, move_vec);
        else
            translate_object(data->scene->obj_selected, move_vec);
        need_redrow = 1;
    }
	// rotation
	if (key == KEY_LEFT)
	{
        if(!data->control_cam)
            rotate_objects(data->scene->obj_selected, -ROTATE_SPEED);
        else
            rotate_cam(&data->scene->cam, -ROTATE_SPEED);
        need_redrow = 1;
    }
	else if (key == KEY_RIGHT)
    {
        if(!data->control_cam)
            rotate_objects(data->scene->obj_selected, ROTATE_SPEED);
        else
            rotate_cam(&data->scene->cam, ROTATE_SPEED);
        need_redrow = 1;
    }
	else if (key == KEY_UP)
	{
		if(!data->control_cam)
			rotate_objects_x(data->scene->obj_selected, -ROTATE_SPEED);
		else
			rotate_cam_x(&data->scene->cam, -ROTATE_SPEED);
	}
	else if (key == KEY_DOWN)
	{
		if(!data->control_cam)
			rotate_objects_x(data->scene->obj_selected, ROTATE_SPEED);
		else
			rotate_cam_x(&data->scene->cam, ROTATE_SPEED);
	}
    // size
    if(!data->control_cam)
    {
        if (key == KEY_PLUS && data->scene->obj_selected)
        {
            resize_objects(data->scene->obj_selected, RESIZE_SPEED);
            need_redrow = 1;
        }
	    else if (key == KEY_MINUS && data->scene->obj_selected)
        {
            resize_objects(data->scene->obj_selected, -RESIZE_SPEED);
            need_redrow = 1;
        }
    }
    if(need_redrow)
        redraw_scene(data, data->scene);
	return (0);
}



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
    printf("controlling obj"); // mb add coords of obj, type, etc
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

void    translate_cam(t_cam *cam, t_vec3 move_vec)
{
    cam->orient.origin = vector_add(cam->orient.origin, move_vec);
    setup_camera_angle(cam);
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
		pl->normal.direction = vec_normalize(rotate_y(pl->normal.direction, angle));
	}
	else if (node->obj_type == CY)
	{
		cy = (t_cy *)node->obj;
		cy->normal.direction = vec_normalize(rotate_y(cy->normal.direction, angle));
	}
}

void	rotate_objects_x(t_olist *node, float angle)
{
	t_pl	*pl;
	t_cy	*cy;

	if (!node)
		return ;
	if (node->obj_type == PL)
	{
		pl = (t_pl *)node->obj;
		pl->normal.direction = vec_normalize(rotate_x(pl->normal.direction, angle));
	}
	else if (node->obj_type == CY)
	{
		cy = (t_cy *)node->obj;
		cy->normal.direction = vec_normalize(rotate_x(cy->normal.direction, angle));
	}
}

void    rotate_cam(t_cam *cam, float angle)
{
    cam->orient.direction = vec_normalize(rotate_y(cam->orient.direction, angle));
    setup_camera_angle(cam);
}

void    rotate_cam_x(t_cam *cam, float angle)
{
    cam->orient.direction = vec_normalize(rotate_x(cam->orient.direction, angle));
    setup_camera_angle(cam);
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

t_vec3 rotate_x(t_vec3 current, float angle)
{
	t_vec3 rotated;
	float cosinus;
	float sinus;

	cosinus = cosf(angle);
	sinus = sinf(angle);
	rotated.x = current.x;
	rotated.y = current.y * cosinus - current.z * sinus;
	rotated.z = current.y *sinus + current.z * cosinus;
	rotated.w = current.w;
	return (rotated);
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