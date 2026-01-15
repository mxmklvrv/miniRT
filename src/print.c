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
	printf("%f ", scene->cam.view_point.x);
	printf("%f ", scene->cam.view_point.y);
	printf("%f \n", scene->cam.view_point.z);
	printf("3D norm orientation vector, in the range [-1,1] for x, y, z axis:");
	printf("%f ", scene->cam.orient.x);
	printf("%f ", scene->cam.orient.y);
	printf("%f\n", scene->cam.orient.z);
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
