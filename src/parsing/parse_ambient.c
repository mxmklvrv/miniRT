#include "minirt.h"

int	parse_ambient(char *line, t_scene *scene)
{
	char	**res;
	float	ratio;
	int		colour;

	if (scene->qt_ambiant > 1)
		return (error("Only 1 Ambient is allowed", scene->err_m), 1);
	if (count_elements(line) != 2)
		return (error("Wrong Ambient specs", scene->err_m), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC, NULL), 1);
	ratio = 0.0f;
	colour = 0;
	if (parse_float(res[0], 0.0f, 1.0f, &ratio) == 1)
		return (error("Invalid Ambient ratio", scene->err_m), free_array(res),
			1);
	if (parse_rgb(res[1], &colour) == 1)
		return (error("Invalid Ambient colour", scene->err_m), free_array(res),
			1);
	scene->ambient.amb = ratio;
	scene->ambient.colour = colour;
	free_array(res);
	return (0);
}
