/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:51:58 by mklevero          #+#    #+#             */
/*   Updated: 2026/04/02 16:53:28 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	init_light(t_light *light, char **res, t_scene *scene);

int	parse_light(char *line, t_scene *scene)
{
	char	**res;
	t_light	*light;

	if (count_elements(line) != 3)
		return (error_return(ERR_LIGT_SPEC, scene->error_line));
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (error_return(ERR_ALLOC, NULL));
	res = ft_split(line, ' ');
	if (!res)
		return (parse_error(scene, ERR_ALLOC, NULL, light));
	if (init_light(light, res, scene))
		return (parse_error(scene, NULL, res, light));
	if (add_light_to_list(scene, light))
		return (parse_error(scene, "error light list", res, light));
	free_array(res);
	return (0);
}

static int	init_light(t_light *light, char **res, t_scene *scene)
{
	light->pos.w = 1;
	if (parse_vector(res[0], &light->pos, MIN_RANGE, MAX_RANGE))
		return (error_return(ERR_LIGT_POS, scene->error_line));
	if (parse_float(res[1], 0.0f, 1.0f, &light->bright))
		return (error_return(ERR_LIGT_BRIT, scene->error_line));
	if (parse_rgb(res[2], &light->color))
		return (error_return(ERR_LIGT_COLOR, scene->error_line));
	return (0);
}
