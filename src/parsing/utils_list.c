#include "minirt.h"

static void	dirty_thoughts(t_scene *scene, t_shape *shape);

int	add_to_list(t_scene *scene, t_shape *shape)
{
	t_olist	*new;
	t_olist	*temp;

	new = malloc(sizeof(t_olist));
	if (!new)
		return (1);
	dirty_thoughts(scene, shape);
	new->shape = shape;
	new->next = NULL;
	if (scene->obj_list == NULL)
		scene->obj_list = new;
	else
	{
		temp = scene->obj_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}
// // add light id num
// int add_light_to_list(t_scene *scene, t_light *light) // new
// {
//     t_llist *new;
//     t_llist *temp;

//     new = malloc(sizeof(t_llist));
//     if(!new)
//         return (1);
//     new->light = light;
//     new->next = NULL;
//     if(scene->light_list == NULL)
//         scene->light_list = new;
//     else
//     {
//         temp = scene->light_list;
//         while(temp->next)
//             temp = temp->next;
//         temp->next = new;
//     }
//     return (0);
// }

static void	dirty_thoughts(t_scene *scene, t_shape *shape)
{
	if (scene->next_obj_id == INT_MAX - 1 || scene->next_obj_id == INT_MAX)
		shape->obj_id = 42;
	else
		shape->obj_id = scene->next_obj_id++;
}