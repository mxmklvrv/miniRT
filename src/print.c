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
		printf("Object enunm num %d\n", curr->obj_type);
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

void	print_vector(char *name, t_vec3	vector)
{
	printf("\nVector %s\n(x: %f, y: %f, z: %f, w: %f)\n", name,
			vector.x, vector.y, vector.z, vector.w);
}

void	print_color(char *name, int color)
{
	printf("\nColor %s: %i\nop: %i\nr: %i\ng: %i\nb: %i\n", name,
		color, get_opacity(color), get_red(color), get_green(color), get_blue(color));
}

void	print_matrix(t_matrix matrix)
{
	int	i;
	int	j;

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
