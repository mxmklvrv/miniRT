/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:55:44 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:55:46 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//int	handle_translation(t_data *data)
//{
//	t_move_state	*move;
//	t_vec3			move_vec;

//	move = data->move_state;
//	move_vec = new_vector(0, 0, 0);
//	if (data->control_cam)
//		cam_move_calculation(data, &move_vec, move);
//	// else if (data->control_light)
//	// 	obj_light_move_calculation(&move_vec, move);
//	else
//		obj_light_move_calculation(&move_vec, move);
//	if (move_vec.x != 0 || move_vec.y != 0 || move_vec.z != 0)
//	{
//		if (data->control_cam)
//			translate_cam(&data->scene->cam, move_vec);
//		else if (data->control_light)
//			translate_light(&data->scene->light, move_vec);
//		else if (data->scene->obj_selected)
//			translate_object(data->scene->obj_selected, move_vec);
//		return (1);
//	}
//	return (0);
//}

void	translate_object(t_olist *node, t_vec3 move_vec)
{
	t_shape	*obj;

	if (!node || !node->shape)
		return ;
	obj = node->shape;
	if (obj->obj_type == SP)
		obj->center = vector_add(obj->center, move_vec);
	else if (obj->obj_type == PL)
		obj->normal.origin = vector_add(obj->normal.origin, move_vec);
	else if (obj->obj_type == CY)
		obj->normal.origin = vector_add(obj->normal.origin, move_vec);
}

void	translate_cam(t_cam *cam, t_vec3 move_vec)
{
	cam->orient.origin = vector_add(cam->orient.origin, move_vec);
}

//void	translate_light(t_light *light, t_vec3 move_vec)
//{
//	if (!light)
//		return ;
//	light->pos = vector_add(light->pos, move_vec);
//}
