/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:51:49 by mklevero          #+#    #+#             */
/*   Updated: 2026/04/02 16:53:28 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	init_cylinder(t_shape *shape, char **res, t_scene *scene);

int	parse_cylinder(char *line, t_scene *scene)
{
	char	**res;
	t_shape	*shape;

	if (count_elements(line) != 5)
		return (error_return(ERR_CY_SPEC, scene->error_line));
	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (error_return(ERR_ALLOC, NULL));
	res = ft_split(line, ' ');
	if (!res)
		return (parse_error(scene, ERR_ALLOC, NULL, shape));
	if (init_cylinder(shape, res, scene))
		return (parse_error(scene, NULL, res, shape));
	if (add_to_list(scene, shape) == 1)
		return (parse_error(scene, ERR_CY_LIST, res, shape));
	free_array(res);
	return (0);
}

static int	init_cylinder(t_shape *shape, char **res, t_scene *scene)
{
	shape->obj_type = CY;
	shape->normal.origin.w = 1;
	if (parse_vector(res[0], &shape->normal.origin, MIN_RANGE, MAX_RANGE))
		return (error_return(ERR_CY_CNTR, scene->error_line));
	shape->normal.direction.w = 0;
	if (parse_vector(res[1], &shape->normal.direction, -1.0f, 1.0f))
		return (error_return(ERR_CY_AXIS, scene->error_line));
	if (parse_float(res[2], 0.0f, 100.0f, &shape->radius)
		|| shape->radius <= 0.0f)
		return (error_return(ERR_CY_DIAM, scene->error_line));
	if (parse_float(res[3], 0.0f, 100.0f, &shape->half_height)
		|| shape->half_height <= 0.0f)
		return (error_return(ERR_CY_HGHT, scene->error_line));
	if (parse_rgb(res[4], &shape->color))
		return (error_return(ERR_CY_COLR, scene->error_line));
	shape->normal.direction = vector_normalize(shape->normal.direction);
	shape->radius = shape->radius / 2.0f;
	shape->half_height = shape->half_height / 2.0f;
	return (0);
}
