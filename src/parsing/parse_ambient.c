#include "minirt.h"

int	parse_ambient(char *line, t_scene *scene)
{
	char	**res;
	float	ratio;
	int		color;

	if (scene->qt_ambiant > 1)
		return (error_return(ERR_AMB_QTY, scene->error_line));
	if (count_elements(line) != 2)
		return (error_return(ERR_AMB_SPEC, scene->error_line));
	res = ft_split(line, ' ');
	if (!res)
		return (error_return(ERR_ALLOC, NULL));
	ratio = 0.0f;
	color = 0;
	if (parse_float(res[0], 0.0f, 1.0f, &ratio) == 1)
		return (parse_error(scene,ERR_AMB_RATI, res, NULL));
	if (parse_rgb(res[1], &color) == 1)
		return (parse_error(scene, ERR_AMB_COLR, res, NULL));
	scene->ambient.amb = ratio;
	scene->ambient.color = color;
	free_array(res);
	return (0);
}

