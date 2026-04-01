#include "minirt.h"

static void	dirty_thoughts(t_scene *scene, t_shape *shape, t_light *light);

int	add_to_list(t_scene *scene, t_shape *shape)
{
	printf("123");
	t_olist	*new;
	t_olist	*temp;

	new = malloc(sizeof(t_olist));
	if (!new)
		return (1);
	dirty_thoughts(scene, shape, NULL);
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

int	add_light_to_list(t_scene *scene, t_light *light)
{
	t_llist	*new;
	t_llist	*temp;

	printf("123");
	new = malloc(sizeof(t_llist));
	if (!new)
		return (1);
	dirty_thoughts(scene, NULL, light);
	new->light = light;
	new->next = NULL;
	if (scene->light_list == NULL)
		scene->light_list = new;
	else
	{
		temp = scene->light_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

static void	dirty_thoughts(t_scene *scene, t_shape *shape, t_light *light)
{
	if (shape)
	{
		if (scene->next_obj_id == INT_MAX - 1 || scene->next_obj_id == INT_MAX)
			shape->obj_id = 42;
		else
			shape->obj_id = scene->next_obj_id++;
	}
	if (light)
	{
		if (scene->next_light_id == INT_MAX - 1
			|| scene->next_light_id == INT_MAX)
			light->light_id = 42;
		else
			light->light_id = scene->next_light_id++;
	}
}
