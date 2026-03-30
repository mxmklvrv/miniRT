#include "minirt.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_scene(t_scene *scene)
{
	free_list(scene->obj_list);
	scene->obj_list = NULL;
}

void	free_list(t_olist *list)
{
	t_olist	*temp;

	if (!list)
		return ;
	while (list)
	{
		temp = list->next;
		if (list->shape)
		{
			free_matrix(list->shape->matrix);
			free(list->shape);
		}
		free(list);
		list = temp;
	}
}
