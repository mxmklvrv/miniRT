#include "minirt.h"

static int	init_sphere(t_shape *shape, char **res, t_scene *scene);

int	parse_sphere(char *line, t_scene *scene)
{
	char	**res;
	t_shape	*shape;

	if (count_elements(line) != 3)
		return (error_return(ERR_SP_SPEC, scene->error_line));
	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (error_return(ERR_ALLOC, NULL));
	res = ft_split(line, ' ');
	if (!res)
		return (parse_error(scene, ERR_ALLOC, NULL, shape));
	if (init_sphere(shape, res, scene))
		return (parse_error(scene, NULL, res, shape));
	if (add_to_list(scene, shape) == 1)
		return (parse_error(scene, ERR_SP_LIST, res, shape));
	free_array(res);
	return (0);
}

static int	init_sphere(t_shape *shape, char **res, t_scene *scene)
{
	shape->obj_type = SP;
	shape->center.w = 1;
	if (parse_vector(res[0], &shape->center, MIN_RANGE, MAX_RANGE))
		return (error_return(ERR_SP_CNTR, scene->error_line));
	if (parse_float(res[1], 0.0f, 100.0f, &shape->radius))
		return (error_return(ERR_SP_DIAM, scene->error_line));
	if (parse_rgb(res[2], &shape->color))
		return (error_return(ERR_SP_COLR, scene->error_line));
	shape->radius = shape->radius / 2.0f;
	return (0);
}
