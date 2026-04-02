/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:38:54 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:38:56 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		printf("Controlling Sphere Nº%d: x=%.2f y=%.2f z=%.2f\n", obj->obj_id,
			obj->center.x, obj->center.y, obj->center.z);
	else if (obj->obj_type == PL)
		printf("Controlling Plane Nº%d: x=%.2f y=%.2f z=%.2f\n", obj->obj_id,
			obj->normal.origin.x, obj->normal.origin.y, obj->normal.origin.z);
	else if (obj->obj_type == CY)
		printf("Controlling Cylinder Nº%d: x=%.2f y=%.2f z=%.2f\n", obj->obj_id,
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
		printf("Controlling Light Nº%d, origin: x=%.2f y=%.2f z=%.2f\n",
			data->scene->light_selected->light->light_id,
			data->scene->light_list->light->pos.x,
			data->scene->light_list->light->pos.y,
			data->scene->light_list->light->pos.z);
	}
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
