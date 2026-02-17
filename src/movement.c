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
#define KEY_PLUS 61 // resize up
#define KEY_MINUS 45 // resize down
#define KEY_ESC 65307 // esc

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
    else if(key == KEY_C)
    {
        data->control_cam = 1;
        printf("controling cam");
    }
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
	if (key == KEY_W)
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
    // size
	else if (key == KEY_PLUS)
		move->resize_up = 0;
	else if (key == KEY_MINUS)
		move->resize_down = 0;
	return (0);
}

int render_hook(t_data *data)
{
    apply_movement(data);
    return (0);
}



void set_hooks(t_data *data)
{
    // check if malloc fails
    // probably will do that in init 
    data->move_state = ft_calloc(1, sizeof(t_move_state)); 
    data->control_cam = 0;

    mlx_hook(data->win, 2, 1L<<0, key_press_hook, data);
    mlx_hook(data->win, 3, 1L<<1, key_release_hook, data);
    mlx_hook(data->win, 17, 0, mlx_loop_end, data->mlx);

    mlx_loop_hook(data->mlx, render_hook, data);


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
void    rotate_cam(t_cam *cam, float angle)
{
    cam->orient.direction = vec_normalize(rotate_y(cam->orient.direction, angle));
    setup_camera_angle(cam);
}


void	apply_movement(t_data *data)
{
    t_move_state *move;
	t_vec3	move_vec;
    int need_redraw;

    need_redraw = 0;
    move = data->move_state;
	move_vec = new_vector(0, 0, 0);

    if(move->forward)
        move_vec = vector_add(move_vec, new_vector(0,0,-MOVE_SPEED));
    if(move->backward)
        move_vec = vector_add(move_vec, new_vector(0,0,MOVE_SPEED));
    if(move->left)
        move_vec = vector_add(move_vec, new_vector(-MOVE_SPEED,0,0));
    if(move->right)
        move_vec = vector_add(move_vec, new_vector(MOVE_SPEED,0,0));
    if(move->up)
        move_vec = vector_add(move_vec, new_vector(0, MOVE_SPEED, 0));
    if(move->down)
        move_vec = vector_add(move_vec, new_vector(0, -MOVE_SPEED, 0));

    // to check if we pressed smth
    if(move_vec.x != 0 || move_vec.y != 0 || move_vec.z !=0)
    {
        if(data->control_cam)
            translate_cam(&data->scene->cam, move_vec);
        else
            translate_object(data->scene->obj_selected, move_vec);
        need_redraw = 1;
    }
    if(move->rotate_left)
    {
        if(data->scene->obj_selected)
            rotate_objects(data->scene->obj_selected, -ROTATE_SPEED);
        else if(data->control_cam)
            rotate_cam(&data->scene->cam, -ROTATE_SPEED);
        need_redraw = 1;
    }
    if(move->rotate_right)
    {
        if(data->scene->obj_selected)
            rotate_objects(data->scene->obj_selected, ROTATE_SPEED);
        else if(data->control_cam)
            rotate_cam(&data->scene->cam, ROTATE_SPEED);
        need_redraw = 1;
    }
    if(move->resize_up)
    {
        if(data->scene->obj_selected && !data->control_cam)
        {
            resize_objects(data->scene->obj_selected, RESIZE_SPEED);
            need_redraw = 1;
        }
    }
    if(move->resize_down)
    {
        if(data->scene->obj_selected && !data->control_cam)
        {
            resize_objects(data->scene->obj_selected, -RESIZE_SPEED);
            need_redraw = 1;
        }
    }
    if(need_redraw)
        redraw_scene(data, data->scene);
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
		pl->normal.direction = vec_normalize(rotate_y(pl->normal.direction, angle));
	}
	else if (node->obj_type == CY)
	{
		cy = (t_cy *)node->obj;
		cy->normal.direction = vec_normalize(rotate_y(cy->normal.direction, angle));
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



// VERSION WITH CONTINUOUS MOVEMENT  END


// VERSION WITH ON RELEASE MOVEMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



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



void set_hooks(t_data *data)
{
    // need to remove movestate from data struct
    data->control_cam = 0;

    mlx_hook(data->win, 2, 1L<<0, key_press_hook, data);
    mlx_hook(data->win, 3, 1L<<1, key_release_hook, data);
    mlx_hook(data->win, 17, 0, mlx_loop_end, data->mlx);

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
void    rotate_cam(t_cam *cam, float angle)
{
    cam->orient.direction = vec_normalize(rotate_y(cam->orient.direction, angle));
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