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

// #define MOVE_SPEED 0.5f
// #define ROTATE_SPEED 0.1f
// #define RESIZE_SPEED 0.2f

// #define KEY_W 119       // forward
// #define KEY_A 97        // left
// #define KEY_S 115       // back
// #define KEY_D 100       // right
// #define KEY_Q 113       // up
// #define KEY_E 101       // down
// #define KEY_C 99        // cam
// #define KEY_TAB 65289   // switch obj
// #define KEY_LEFT 65361  // rotate left
// #define KEY_RIGHT 65363 // rotate right
// #define KEY_UP 65362    // rotate up
// #define KEY_DOWN 65364  // rotate down
// #define KEY_PLUS 61     // resize up
// #define KEY_MINUS 45    // resize down
// #define KEY_ESC 65307   // esc

// #define KEY_H 104 // height up
// #define KEY_J 106 // height down

// typedef enum e_axis
// {
// 	Y_AXIS,
// 	X_AXIS
// }		t_axis;

// VERSION WITH ON RELEASE MOVEMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// void	set_hooks(t_data *data)
// {
// 	// need to remove movestate from data struct
// 	data->control_cam = 0;
// 	mlx_hook(data->win, 2, 1L << 0, key_press_hook, data);
// 	mlx_hook(data->win, 3, 1L << 1, key_release_hook, data);
// 	mlx_hook(data->win, 17, 0, mlx_loop_end, data->mlx);
// }

int	key_press_hook(int key, t_data *data)
{
	printf("scene ptr: %p\n", data->scene);
	printf("Key pressed: %d\n", key);
	if (key == KEY_C)
	{
		data->control_cam = !data->control_cam;
		printf("controling cam\n");
	}
	else if (key == KEY_TAB)
		select_object(data->scene);
	else if (key == KEY_ESC)
		mlx_loop_end(data->mlx);
	return (0);
}
// clean version
// int	key_release_hook(int key, t_data *data)
// {
// 	int	need_redraw;

// 	need_redraw = 0;
// 	printf("obj_selected: %p\n", data->scene->obj_selected);
// 	if (data->scene->obj_selected)
// 		printf("obj_type: %d\n", data->scene->obj_selected->obj_type);
// 	if (handle_translation(key, data))
// 		need_redraw = 1;
// 	if (handle_rotation(key, data))
// 		need_redraw = 1;
// 	if (handle_resize(key, data))
// 		need_redraw = 1;
// 	if (need_redraw)
// 		redraw_scene(data, data->scene);
// 	printf("Key release hook\n");
// 	return (0);
// }

int	key_release_hook(int key, t_data *data)
{
	int	need_redraw;

	need_redraw = 0;
	// printf("obj_selected: %p\n", data->scene->obj_selected);
	// if (data->scene->obj_selected)
	// 	printf("obj_type: %d\n", data->scene->obj_selected->obj_type);
	if (handle_translation(key, data)){
		print_pos(data->scene);
		need_redraw = 1;
	}
	if (handle_rotation(key, data)){
		print_pos(data->scene);
		need_redraw = 1;
	}
	if (handle_resize(key, data)){
		print_pos(data->scene);
		need_redraw = 1;
	}
	if (need_redraw)
		redraw_scene(data, data->scene);
	return (0);
}


// add translate light
// clean version
int	handle_translation(int key, t_data *data)
{
	t_vec3	move_vec;

	move_vec = new_vector(0, 0, 0);
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
	if (move_vec.x != 0 || move_vec.y != 0 || move_vec.z != 0)
	{
		if (data->control_cam)
			translate_cam(&data->scene->cam, move_vec);
		else if (data->scene->obj_selected)
			translate_object(data->scene->obj_selected, move_vec);
		return (1);
	}
	return (0);
}



// light cannot be rotated
int	handle_rotation(int key, t_data *data)
{
	if (key == KEY_LEFT)
	{
		rotate_obj_or_cam(data, -ROTATE_SPEED, Y_AXIS);
		return (1);
	}
	if (key == KEY_RIGHT)
	{
		rotate_obj_or_cam(data, ROTATE_SPEED, Y_AXIS);
		return (1);
	}
	if (key == KEY_UP)
	{
		rotate_obj_or_cam(data, -ROTATE_SPEED, X_AXIS);
		return (1);
	}
	if (key == KEY_DOWN)
	{
		rotate_obj_or_cam(data, ROTATE_SPEED, X_AXIS);
		return (1);
	}
	return (0);
}

// can we resize light ?? Looks like no
int	handle_resize(int key, t_data *data)
{
	if (!data->scene->obj_selected || data->scene->obj_selected->obj_type == PL
		|| data->control_cam)
		return (0); // or data->light // !data || !data->scene ||
	return (0);
	if (key == KEY_PLUS && resize_diameter(data->scene->obj_selected,
			RESIZE_SPEED))
		return (1);
	if (key == KEY_MINUS && resize_diameter(data->scene->obj_selected,
			-RESIZE_SPEED))
		return (1);
	if (key == KEY_H && resize_height(data->scene->obj_selected, RESIZE_SPEED))
		return (1);
	if (key == KEY_J && resize_height(data->scene->obj_selected, -RESIZE_SPEED))
		return (1);
	return (0);
}

// need to add light
void	rotate_obj_or_cam(t_data *data, float angle, t_axis axis)
{
	if (data->control_cam)
		rotate_cam(&data->scene->cam, angle, axis);
	else if (data->scene->obj_selected)
		rotate_objects(data->scene->obj_selected, angle, axis);
}

/**
 * If there is next obj - select it
 * Otherwise select the first one
 */
void	select_object(t_scene *scene)
{
	printf("Selecting object\n");
	printf("scene: %p\n", scene);
	printf("obj_list: %p\n", scene->obj_list);
	if (!scene->obj_selected)
		scene->obj_selected = scene->obj_list;
	else if (scene->obj_selected->next)
		scene->obj_selected = scene->obj_selected->next;
	else
		scene->obj_selected = scene->obj_list;
	printf("controlling obj\n"); // mb add coords of obj, type, etc
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
		printf("trans obj SP\n");
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

void	rotate_objects(t_olist *node, float angle, t_axis axis)
{
	t_pl	*pl;
	t_cy	*cy;

	if (!node || node->obj_type == SP)
		return ;
	if (node->obj_type == PL)
	{
		pl = (t_pl *)node->obj;
		if (axis == Y_AXIS)
			pl->normal.direction = vector_normalize(rotate_y(pl->normal.direction,
						angle));
		else
			pl->normal.direction = vector_normalize(rotate_x(pl->normal.direction,
						angle));
	}
	else if (node->obj_type == CY)
	{
		cy = (t_cy *)node->obj;
		if (axis == Y_AXIS)
			cy->normal.direction = vector_normalize(rotate_y(cy->normal.direction,
						angle));
		else
			cy->normal.direction = vector_normalize(rotate_x(cy->normal.direction,
						angle));
	}
}

void	rotate_cam(t_cam *cam, float angle, t_axis axis)
{
	if (axis == Y_AXIS)
		cam->orient.direction = vector_normalize(rotate_y(cam->orient.direction,
					angle));
	else if (axis == X_AXIS)
		cam->orient.direction = vector_normalize(rotate_x(cam->orient.direction,
					angle));
	setup_camera_angle(cam);
}

void	translate_cam(t_cam *cam, t_vec3 move_vec)
{
	cam->orient.origin = vector_add(cam->orient.origin, move_vec);
	setup_camera_angle(cam);
}

// resizing diam of sp and cy
int	resize_diameter(t_olist *node, float value)
{
	t_sp	*sp;
	t_cy	*cy;

	if (!node || node->obj_type == PL)
		return (0);
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
		if (cy->diameter < 0.1f)
			cy->diameter = 0.1f;
	}
	return (1);
}

int	resize_height(t_olist *node, float value)
{
	t_cy	*cy;

	if (!node || node->obj_type != CY)
		return (0);
	cy = (t_cy *)node->obj;
	cy->height += value;
	if (cy->height < 0.1f)
		cy->height = 0.1f;
	return (1);
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

t_vec3	rotate_x(t_vec3 current, float angle)
{
	t_vec3	rotated;
	float	cosinus;
	float	sinus;

	cosinus = cosf(angle);
	sinus = sinf(angle);
	rotated.x = current.x;
	rotated.y = current.y * cosinus - current.z * sinus;
	rotated.z = current.y * sinus + current.z * cosinus;
	rotated.w = current.w;
	return (rotated);
}

// int	key_release_hook(int key, t_data *data)
// {
// 	t_vec3 move_vec;

//     move_vec = new_vector(0, 0, 0);

// 	if (key == KEY_W)
// 		move_vec.z -= MOVE_SPEED;
// 	else if (key == KEY_S)
// 		move_vec.z += MOVE_SPEED;
// 	else if (key == KEY_A)
// 		move_vec.x -= MOVE_SPEED;
// 	else if (key == KEY_D)
// 		move_vec.x += MOVE_SPEED;
// 	else if (key == KEY_Q)
// 		move_vec.y += MOVE_SPEED;
// 	else if (key == KEY_E)
// 		move_vec.y -= MOVE_SPEED;
//     if(move_vec.x != 0 || move_vec.y != 0 || move_vec.z !=0)
//     {
//         if(data->control_cam)
//             translate_cam(&data->scene->cam, move_vec);
//         else
//             translate_object(data->scene->obj_selected, move_vec);
//     }
// 	// rotation
// 	if (key == KEY_LEFT)
// 	{
//         if(!data->control_cam)
//             rotate_objects(data->scene->obj_selected, -ROTATE_SPEED);
//         else
//             rotate_cam(&data->scene->cam, -ROTATE_SPEED);

//     }
// 	else if (key == KEY_RIGHT)
//     {
//         if(!data->control_cam)
//             rotate_objects(data->scene->obj_selected, ROTATE_SPEED);
//         else
//             rotate_cam(&data->scene->cam, ROTATE_SPEED);
//     }
// 	else if (key == KEY_UP)
// 	{
// 		if(!data->control_cam)
// 			rotate_objects_x(data->scene->obj_selected, -ROTATE_SPEED);
// 		else
// 			rotate_cam_x(&data->scene->cam, -ROTATE_SPEED);
// 	}
// 	else if (key == KEY_DOWN)
// 	{
// 		if(!data->control_cam)
// 			rotate_objects_x(data->scene->obj_selected, ROTATE_SPEED);
// 		else
// 			rotate_cam_x(&data->scene->cam, ROTATE_SPEED);
// 	}
//     // size
//     if(!data->control_cam)
//     {
//         if (key == KEY_PLUS && data->scene->obj_selected)
//         {
//             resize_objects(data->scene->obj_selected, RESIZE_SPEED);
//         }
// 			else if (key == KEY_MINUS && data->scene->obj_selected)
//         {
//             resize_objects(data->scene->obj_selected, -RESIZE_SPEED);
//         }
//     }
//     redraw_scene(data, data->scene);
// 	return (0);
// }


void	print_pos(t_scene *scene)
{
	t_olist	*node;

	if (!scene)
		return ;

	node = scene->obj_selected;

	if (!node)
	{
		printf("No object selected\n");
		return ;
	}

	if (node->obj_type == SP)
	{
		t_sp *sp = (t_sp *)node->obj;
		printf("Sphere position: x=%.2f y=%.2f z=%.2f\n",
			sp->sp_center.x,
			sp->sp_center.y,
			sp->sp_center.z);
	}
	else if (node->obj_type == PL)
	{
		t_pl *pl = (t_pl *)node->obj;
		printf("Plane origin: x=%.2f y=%.2f z=%.2f\n",
			pl->normal.origin.x,
			pl->normal.origin.y,
			pl->normal.origin.z);
	}
	else if (node->obj_type == CY)
	{
		t_cy *cy = (t_cy *)node->obj;
		printf("Cylinder origin: x=%.2f y=%.2f z=%.2f\n",
			cy->normal.origin.x,
			cy->normal.origin.y,
			cy->normal.origin.z);
	}
}

// void print_cam_pos(t_scene *scene)
// {
// 	if (!scene)
// 	{
// 		printf("YOLO");
// 		return ;
// 	}
// 	printf("Cam position")
// }