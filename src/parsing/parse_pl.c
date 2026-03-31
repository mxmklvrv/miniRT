#include "minirt.h"

int	parse_plane(char *line, t_scene *scene)
{
	char	**res;
	t_shape *shape;

	if (count_elements(line) != 3)
		return (error_return(ERR_PL_SPEC, scene->err_m));
	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (error_return(ERR_ALLOC, NULL));
	res = ft_split(line, ' ');
	if (!res)
		return (parse_error(scene, ERR_ALLOC, NULL, shape));
	if(init_plane(shape, res, scene))
		return (parse_error(scene, NULL, res, shape));
	if (add_to_list(scene, shape) == 1)
		return (parse_error(scene, ERR_PL_LIST, res, shape));
	free_array(res);
	return (0);
}

int init_plane(t_shape *shape, char **res, t_scene *scene)
{
	shape->obj_type = PL;
	shape->normal.origin.w = 1;
	if (parse_vector(res[0], &shape->normal.origin, -100.0f, 100.0f) == 1)
		return (error_return(ERR_PL_POINT, scene->err_m));
	shape->normal.direction.w = 0;
	if (parse_vector(res[1], &shape->normal.direction, -1.0f, 1.0f) == 1)
		return (error_return(ERR_PL_NORM, scene->err_m));
	if (parse_rgb(res[2], &shape->color) == 1)
		return (error_return(ERR_PL_COLR, scene->err_m));
	return (0);
}

