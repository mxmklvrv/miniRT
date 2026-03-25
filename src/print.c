#include "minirt.h"

void	print_list(t_scene *scene)
{
	t_olist	*curr;
	int		i;

	curr = scene->obj_list;
	i = 0;
	while (curr)
	{
		printf("Objects num  %d in object list\n", i);
		printf("Object enunm num %d\n", curr->shape->obj_type);
		curr = curr->next;
		i++;
	}
	printf("End printing object list\n");
}

void	print_vars(t_scene *scene)
{
	printf("TESTING PARSING\n");
	printf("---------------------------------------------------\n");
	printf("Ambient Parsing\n");
	printf("Ambient lighting ratio in the range [0.0,1.0]: ");
	printf("%f\n", scene->ambient.amb);
	printf("Ambient R, G, B colors in the range [0-255]: ");
	printf("%d\n", scene->ambient.color);
	printf("---------------------------------------------------\n");
	printf("Camera Parsing\n");
	printf("x, y, z coordinates of the viewpoint: ");
	printf("%f ", scene->cam.orient.origin.x);
	printf("%f ", scene->cam.orient.origin.y);
	printf("%f \n", scene->cam.orient.origin.z);
	printf("3D norm orientation vector, in the range [-1,1] for x, y, z axis:");
	printf("%f ", scene->cam.orient.direction.x);
	printf("%f ", scene->cam.orient.direction.y);
	printf("%f\n", scene->cam.orient.direction.z);
	printf("FOV: Horizontal field of view in degrees in the range [0,180]: ");
	printf("%f\n", scene->cam.fov);
	printf("---------------------------------------------------\n");
	printf("Light Parsing\n");
	printf("x, y, z coordinates of the light point: ");
	printf("%f ", scene->light.pos.x);
	printf("%f ", scene->light.pos.y);
	printf("%f \n", scene->light.pos.z);
	printf("the light brightness ratio in the range [0.0,1.0]: ");
	printf("%f \n", scene->light.bright);
	printf("(BONUS) R, G, B colors in the range [0-255]: ");
	printf("%d\n\n", scene->light.color);
}

void	print_pos(t_scene *scene)
{
	t_shape	*obj;

	if (!scene || !scene->obj_selected)
	{
		printf("No object selected\n");
		return ;
	}
	obj = scene->obj_selected->shape;
	if (obj->obj_type == SP)
		printf("Controlling Sphere Nº%d : x=%.2f y=%.2f z=%.2f\n", obj->obj_id,
			obj->center.x, obj->center.y, obj->center.z);
	else if (obj->obj_type == PL)
		printf("Controlling Plane Nº%d: x=%.2f y=%.2f z=%.2f\n", obj->obj_id,
			obj->normal.origin.x, obj->normal.origin.y, obj->normal.origin.z);
	else if (obj->obj_type == CY)
		printf("Controlling Cylinder Nº%d : x=%.2f y=%.2f z=%.2f\n", obj->obj_id,
			obj->normal.origin.x, obj->normal.origin.y, obj->normal.origin.z);
}

void	print_cam_light_pos(t_data *data)
{
	if (!data->scene)
	{
		printf("YOLO");
		return ;
	}
	if (data->control_cam == 1)
	{
		printf("Controlling Cam, origin: x=%.2f y=%.2f z=%.2f",
			data->scene->cam.orient.origin.x, data->scene->cam.orient.origin.y,
			data->scene->cam.orient.origin.z);
		printf(" and direct: x=%.2f y=%.2f z=%.2f\n",
			data->scene->cam.orient.direction.x,
			data->scene->cam.orient.direction.y,
			data->scene->cam.orient.direction.z);
	}
	if (data->control_light == 1)
	{
		printf("Controlling Light, origin: x=%.2f y=%.2f z=%.2f\n",
			data->scene->light.pos.x, data->scene->light.pos.y,
			data->scene->light.pos.z);
	}
}

void	print_vector(t_vec3 vector)
{
	if (is_point(vector))
		printf("point ");
	else
		printf("vector ");
	printf("(x: %f, y: %f, z: %f)\n", vector.x, vector.y, vector.z);
}

void	print_ray(t_ray ray)
{
	printf("RAY\norigin: ");
	print_vector(ray.origin);
	printf("direction: ");
	print_vector(ray.direction);
	printf("\n");
}

void	print_color(int color)
{
	printf("\nColor: %i\nop: %i\nr: %i\ng: %i\nb: %i\n", color,
		get_opacity(color), get_red(color), get_green(color), get_blue(color));
}

void	print_matrix(t_matrix matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	j = 0;
	while (matrix.ptr && j < matrix.row)
	{
		i = 0;
		while (matrix.ptr[j] && i < matrix.col)
		{
			printf("| %f ", matrix.ptr[j][i]);
			i++;
		}
		printf("|\n");
		j++;
	}
	printf("%ix%i\n", j, i);
}

void	print_intersection(t_intersection intersection)
{
	int	i;

	printf("INTERSECTION\ncount: %i\n", intersection.count);
	i = 0;
	while (i < intersection.count)
	{
		printf("[%i] %f\n", i, intersection.val[i]);
		i++;
	}
}

void	print_scene(t_scene *scene)
{
	t_olist	*tmp;
	t_shape	*s;

	printf("\n---- SCENE DEBUG ----\n");
	printf("Ambient count: %d\n", scene->qt_ambiant);
	printf("Camera count : %d\n", scene->qt_cam);
	printf("Light count  : %d\n", scene->qt_light);
	printf("\nCamera:\n");
	printf("  pos: %.2f %.2f %.2f\n", scene->cam.orient.origin.x,
		scene->cam.orient.origin.y, scene->cam.orient.origin.z);
	printf("  dir: %.2f %.2f %.2f\n", scene->cam.orient.direction.x,
		scene->cam.orient.direction.y, scene->cam.orient.direction.z);
	printf("  fov: %.2f\n", scene->cam.fov);
	printf("\nLight:\n");
	printf("  pos: %.2f %.2f %.2f\n", scene->light.pos.x, scene->light.pos.y,
		scene->light.pos.z);
	printf("  brightness: %.2f\n", scene->light.bright);
	printf("\nObjects:\n");
	tmp = scene->obj_list;
	while (tmp)
	{
		s = tmp->shape;
		printf("\nObject ID: %d\n", s->obj_id);
		printf("Type: %d\n", s->obj_type);
		if (s->obj_type == SP)
		{
			printf("Sphere center: %.2f %.2f %.2f\n", s->center.x, s->center.y,
				s->center.z);
			printf("Diameter: %.2f\n", s->diameter);
		}
		if (s->obj_type == PL)
		{
			printf("Plane point: %.2f %.2f %.2f\n", s->normal.origin.x,
				s->normal.origin.y, s->normal.origin.z);
			printf("Normal: %.2f %.2f %.2f\n", s->normal.direction.x,
				s->normal.direction.y, s->normal.direction.z);
		}
		if (s->obj_type == CY)
		{
			printf("Cylinder center: %.2f %.2f %.2f\n", s->normal.origin.x,
				s->normal.origin.y, s->normal.origin.z);
			printf("Axis: %.2f %.2f %.2f\n", s->normal.direction.x,
				s->normal.direction.y, s->normal.direction.z);
			printf("Diameter: %.2f\n", s->diameter);
			printf("Height: %.2f\n", s->height);
		}
		printf("Color: %d\n", s->color);
		tmp = tmp->next;
	}
	printf("\n---------------------\n");
}

void	user_manual(void)
{
	printf("\n========== MINI RT USER MANUAL ==========\n\n");

	printf("GENERAL:\n");
	printf("  TAB        - Select next object\n");
	printf("  C          - Toggle camera control\n");
	printf("  L          - Toggle light control\n");
	printf("  ESC        - Exit program\n\n");

	printf("MOVEMENT (WASDQE):\n");
	printf("  W / S      - Forward / Backward\n");
	printf("  A / D      - Left / Right\n");
	printf("  Q / E      - Up / Down\n\n");

	printf("ROTATION (Arrow Keys):\n");
	printf("  LEFT/RIGHT - Rotate left / right\n");
	printf("  UP/DOWN    - Rotate up / down\n\n");

	printf("RESIZE:\n");
	printf("  + / -      - Increase / Decrease size\n");
	printf("  H / J      - Increase / Decrease height (Cylinder only)\n\n");

	printf("MODES:\n");
	printf("  Object mode  - Default (TAB to switch objects)\n");
	printf("  Camera mode  - Press C\n");
	printf("  Light mode   - Press L\n\n");

	printf("========================================\n\n");
}