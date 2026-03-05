#include "minirt.h"

// 0.0,0.0,-10.0  0.0,1.0,0.0  0,0,225
// !!!!!!!!!!!!!!!dirty version for tests!!!!!!!!!!!!!!!!!!!!!!
// int	parse_plane(char *line, t_scene *scene)
// {
// 	char	**res;
// 	t_pl	*plane;
// 	int		colour;

// 	if (count_elements(line) != 3)
// 		return (error("Invalid specs for plane", scene->err_m), 1);
// 	plane = malloc(sizeof(t_pl));
// 	if (!plane)
// 		return (error(ERR_ALLOC, NULL), 1);
// 	res = ft_split(line, ' ');
// 	if (!res)
// 		return (error(ERR_ALLOC, NULL), free(plane), 1);
// 	if (parse_vector(res[0], &plane->normal.origin, -100.0f, 100.0f) == 1)
// 		return (error("Invalid coordinates of a point in plane", scene->err_m),
// 			free(plane), free_array(res), 1);
// 	if (parse_vector(res[1], &plane->normal.direction, 0.0f, 1.0f) == 1)
// 		return (error("Invalid normal vector for plane", scene->err_m),
// 			free(plane), free_array(res), 1);
// 	colour = 0;
// 	if (parse_rgb(res[2], &colour) == 1)
// 		return (error("Invalid plane colour", scene->err_m), free(plane),
// 			free_array(res), 1);
// 	plane->colour = colour;
// 	if (add_to_list(&scene->obj_list, plane, PL, plane->colour) == 1)
// 		return (error("Failed adding plane to the list", scene->err_m),
// 			free(plane), free_array(res), 1);
// 	printf("PLANE\n");
// 	printf("pl point %f %f %f\n", plane->normal.origin.x, plane->normal.origin.y,
// 		plane->normal.origin.z);
// 	printf("norm %f %f %f\n", plane->normal.direction.x, plane->normal.direction.y,
// 		plane->normal.direction.z);
// 	printf("color %d\n\n", plane->colour);
// 	return (free_array(res), 0);
// }


// new version for shape
int	parse_plane(char *line, t_scene *scene)
{
	char	**res;
	t_shape *shape;

	if (count_elements(line) != 3)
		return (error("Invalid specs for plane", scene->err_m), 1);
	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (error(ERR_ALLOC, NULL), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC, NULL), free(shape), 1);
	if(init_plane(shape, res, scene))
		return (free(shape), free_array(res), 1);
	if (add_to_list(&scene->obj_list, shape) == 1)
		return (error("Failed adding plane to the list", scene->err_m),
			free(shape), free_array(res), 1);
	return (free_array(res), 0);
}

int init_plane(t_shape *shape, char **res, t_scene *scene)
{
	shape->obj_type = PL;
	if (parse_vector(res[0], &shape->normal.origin, -100.0f, 100.0f) == 1)
		return (error("Invalid plane point", scene->err_m), 1);
	if (parse_vector(res[1], &shape->normal.direction, -1.0f, 1.0f) == 1)
		return (error("Invalid plane normal", scene->err_m), 1);
	// normilize direction here ?
	if (parse_rgb(res[2], &shape->colour) == 1)
		return (error("Invalid plane colour", scene->err_m), 1);
	return (0);
}

