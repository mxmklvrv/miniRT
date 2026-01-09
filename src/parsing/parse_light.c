#include "minirt.h"

int	parse_light(char *line, t_scene *scene)
{
	char	**res;
	float	bright;
	int		colour;

	if (scene->qt_light > 1)
		return (error("Only 1 light is allowed", NULL), 1);
	if (count_elements(line) != 3) // or 2 for mandotary
		return (error("Invalid light specs", scene->err_m), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC, NULL), 1);
	bright = 0.0f;
	colour = 0;
	if (parse_vector(res[0], &scene->light.pos, -100.0f, 100.0f) == 1)
		return (error("Invalid light position", scene->err_m), free_array(res),
			1);
	if (parse_float(res[1], 0.0f, 1.0f, &bright) == 1)
		return (error("Invalid light brightness", scene->err_m),
			free_array(res), 1);
	if (parse_rgb(res[2], &colour) == 1) // this is for bonus
		return (error("Invalid light colour", scene->err_m), free_array(res),
			1);
	scene->light.bright = bright;
	scene->light.color = colour; // this is for bonus
	free_array(res);
	return (0);
}
