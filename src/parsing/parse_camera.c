/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:51:42 by mklevero          #+#    #+#             */
/*   Updated: 2026/04/02 18:00:41 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_cam(t_scene *scene, float fov);

int	parse_cam(char *line, t_scene *scene)
{
	char	**res;
	float	fov;

	if (scene->qt_cam > 1)
		return (error_return(ERR_CAM_QTY, scene->error_line));
	if (count_elements(line) != 3)
		return (error_return(ERR_CAM_SPEC, scene->error_line));
	res = ft_split(line, ' ');
	if (!res)
		return (error_return(ERR_ALLOC, NULL));
	scene->cam.orient.origin.w = 1;
	if (parse_vector(res[0], &scene->cam.orient.origin, MIN_RANGE, MAX_RANGE))
		return (parse_error(scene, ERR_CAM_VIEW, res, NULL));
	scene->cam.orient.direction.w = 0;
	if (parse_vector(res[1], &scene->cam.orient.direction, -1.0f, 1.0f))
		return (parse_error(scene, ERR_CAM_ORIT, res, NULL));
	fov = 0;
	if (parse_float(res[2], 0.0f, 180.0f, &fov))
		return (parse_error(scene, ERR_CAM_FOV, res, NULL));
	init_cam(scene, fov);
	free_array(res);
	return (0);
}

static void	init_cam(t_scene *scene, float fov)
{
	if (fov == 180)
		fov = fov - EPSILON;
	scene->cam.fov = fov;
	scene->cam.yaw = atan2f(scene->cam.orient.direction.x,
			scene->cam.orient.direction.z);
	scene->cam.pitch = asinf(scene->cam.orient.direction.y);
}