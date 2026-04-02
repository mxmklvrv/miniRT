/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:52:57 by mklevero          #+#    #+#             */
/*   Updated: 2026/04/02 16:53:22 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free_lights(scene->light_list);
	scene->obj_list = NULL;
	scene->light_list = NULL;
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
			free(list->shape);
		free(list);
		list = temp;
	}
}

void	free_lights(t_llist *list)
{
	t_llist	*temp;

	if (!list)
		return ;
	while (list)
	{
		temp = list->next;
		if (list->light)
			free(list->light);
		free(list);
		list = temp;
	}
}
