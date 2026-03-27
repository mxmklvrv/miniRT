#include "minirt.h"

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

int	init_cylinder(t_shape *shape, char **res, t_scene *scene)
{
	shape->obj_type = CY;
	if (parse_vector(res[0], &shape->normal.origin, -100.0f, 100.0f) == 1)
		return (error_return(ERR_CY_CNTR, scene->error_line));
	shape->normal.origin.w = 1;
	if (parse_vector(res[1], &shape->normal.direction, -1.0f, 1.0f) == 1)
		return (error_return(ERR_CY_AXIS, scene->error_line));
	shape->normal.direction.w = 0;
	if (parse_float(res[2], 0.0f, 100.0f, &shape->diameter) == 1)
		return (error_return(ERR_CY_DIAM, scene->error_line));
	if (parse_float(res[3], 0.0f, 100.0f, &shape->height) == 1)
		return (error_return(ERR_CY_HGHT, scene->error_line));
	if (parse_rgb(res[4], &shape->color) == 1)
		return (error_return(ERR_CY_COLR, scene->error_line));
	shape->axis = vector_normalize(shape->normal.direction);
	shape->radius = shape->diameter / 2.0f;
	shape->half_h = shape->height / 2.0f;
	return (0);
}
