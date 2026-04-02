/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:52:25 by mklevero          #+#    #+#             */
/*   Updated: 2026/04/02 16:53:25 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_line(char *line, t_scene *scene);
static int	postpars_validation(t_scene *scene);

int	parse_input_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_return(ERR_OPEN, NULL));
	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(line, scene))
		{
			free(line);
			return (parse_fatal(scene, fd));
		}
		free(line);
		line = get_next_line(fd);
	}
	if (postpars_validation(scene))
		return (parse_fatal(scene, fd));
	close(fd);
	return (0);
}

static int	parse_line(char *line, t_scene *scene)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \n");
	if (!trimmed)
		return (error_return(ERR_ALLOC, NULL));
	scene->error_line = trimmed;
	if (dispatch(trimmed, scene))
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}

static int	postpars_validation(t_scene *scene)
{
	if (!scene->obj_list)
		return (error_return(ERR_NO_OBJ, NULL));
	if (scene->qt_cam != 1)
		return (error_return(ERR_CAM_NOCAM, NULL));
	if (scene->qt_light > 1)
		return (error_return(ERR_LIGT_QTY, NULL));
	if (scene->qt_ambiant == 0)
	{
		scene->ambient.color = 0;
		scene->ambient.amb = 0;
	}
	if (scene->qt_ambiant == 0 && scene->qt_light == 0)
		return (error_return("Absolute darkness detected", NULL));
	if (scene->qt_light == 1)
		scene->light_list->light->color = new_color(255, 255, 255, 255);
	return (0);
}
