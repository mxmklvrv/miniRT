#include "minirt.h"

void	print_list(t_scene *scene)
{
	t_olist *curr;
	int	i;

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
	printf("%d\n", scene->ambient.colour);
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
	t_olist	*node;

	if (!scene)
		return ;
	node = scene->obj_selected;
	if (!node)
	{
		printf("No object selected\n");
		return ;
	}
	if (node->shape->obj_type == SP)
	{
		printf("Controlling Sphere, coordinates: x=%.2f y=%.2f z=%.2f\n", node->shape->center.x,
			node->shape->center.y, node->shape->center.z);
	}
	else if (node->shape->obj_type == PL)
	{
		printf("Controlling Plane, coordinates: x=%.2f y=%.2f z=%.2f\n", node->shape->normal.origin.x,
			node->shape->normal.origin.y, node->shape->normal.origin.z);
	}
	else if (node->shape->obj_type == CY)
	{
		printf("Contrlling Cylinder, coordinates: x=%.2f y=%.2f z=%.2f\n", node->shape->normal.origin.x,
			node->shape->normal.origin.y, node->shape->normal.origin.z);
	}
}

void	print_cam_pos(t_scene *scene)
{
	if (!scene)
	{
		printf("YOLO");
		return ;
	}
	printf("Controlling Cam, origin: x=%.2f y=%.2f z=%.2f", scene->cam.orient.origin.x,
		scene->cam.orient.origin.y, scene->cam.orient.origin.z);
	printf(" and direct: x=%.2f y=%.2f z=%.2f\n", scene->cam.orient.direction.x,
		scene->cam.orient.direction.y, scene->cam.orient.direction.z);
}

void	print_vector(t_vec3	vector)
{
	if (is_point(vector))
		printf("point ");
	else
		printf("vector ");
	printf("(x: %f, y: %f, z: %f)\n",
			vector.x, vector.y, vector.z);
}

void	print_ray(t_ray	ray)
{
	printf("RAY\norigin: ");
	print_vector(ray.origin);
	printf("direction: ");
	print_vector(ray.direction);
	printf("\n");
}

void	print_color(int color)
{
	printf("\nColor: %i\nop: %i\nr: %i\ng: %i\nb: %i\n",
		color, get_opacity(color), get_red(color), get_green(color), get_blue(color));
}

void	print_matrix(t_matrix matrix)
{
	int	i = 0;
	int	j = 0;

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
