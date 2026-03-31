#include "minirt.h"

int	parse_light(char *line, t_scene *scene)
{
	char	**res;
	float	bright;
	int		color;

	if (scene->qt_light > 1)
		return (error_return(ERR_LIGT_QTY, NULL));
	if (count_elements(line) != 3) // or 2 for mandotary
		return (error_return(ERR_LIGT_SPEC, scene->err_m));
	res = ft_split(line, ' ');
	if (!res)
		return (error_return(ERR_ALLOC, NULL));
	bright = 0.0f;
	color = 0;
	scene->light.pos.w = 1;
	if (parse_vector(res[0], &scene->light.pos, -100.0f, 100.0f) == 1)
		return (parse_error(scene,ERR_LIGT_POS, res, NULL));
	if (parse_float(res[1], 0.0f, 1.0f, &bright) == 1)
		return (parse_error(scene,ERR_LIGT_BRIT,res, NULL));
	if (parse_rgb(res[2], &color) == 1) // this is for bonus
		return (parse_error(scene, ERR_LIGT_COLOR, res, NULL));
	scene->light.bright = bright;
	scene->light.color = new_color(255, 255, 255, 255); // this is for bonus
	free_array(res);
	return (0);
}
