/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:50:23 by mklevero          #+#    #+#             */
/*   Updated: 2026/04/02 16:53:36 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_cam_light(char *line, char ch, t_scene *scene);

int	dispatch(char *line, t_scene *scene)
{
	if (ft_strchr("CAL", *line))
		return (parse_cam_light(line, *line, scene));
	else if (ft_strncmp(line, "sp", 2) == 0)
	{
		line += 2;
		return (parse_sphere(line, scene));
	}
	else if (ft_strncmp(line, "pl ", 2) == 0)
	{
		line += 2;
		return (parse_plane(line, scene));
	}
	else if (ft_strncmp(line, "cy ", 2) == 0)
	{
		line += 2;
		return (parse_cylinder(line, scene));
	}
	else
		return (error_return(ERR_WRONG_CHAR, scene->error_line));
}

static int	parse_cam_light(char *line, char ch, t_scene *scene)
{
	if (ch == 'C')
	{
		scene->qt_cam++;
		return (parse_cam(++line, scene));
	}
	else if (ch == 'A')
	{
		scene->qt_ambiant++;
		return (parse_ambient(++line, scene));
	}
	else if (ch == 'L')
	{
		scene->qt_light++;
		return (parse_light(++line, scene));
	}
	return (0);
}
