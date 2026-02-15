#include "minirt.h"

// 0.0,0.0,-10.0  0.0,1.0,0.0  0,0,225
int	parse_plane(char *line, t_scene *scene)
{
	char	**res;
	t_pl	*plane;
	int		colour;

	if (count_elements(line) != 3)
		return (error("Invalid specs for plane", scene->err_m), 1);
	plane = malloc(sizeof(t_pl));
	if (!plane)
		return (error(ERR_ALLOC, NULL), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC, NULL), free(plane), 1);
	if (parse_vector(res[0], &plane->normal.origin, -100.0f, 100.0f) == 1)
		return (error("Invalid coordinates of a point in plane", scene->err_m),
			free(plane), free_array(res), 1);
	if (parse_vector(res[1], &plane->normal.direction, 0.0f, 1.0f) == 1)
		return (error("Invalid normal vector for plane", scene->err_m),
			free(plane), free_array(res), 1);
	colour = 0;
	if (parse_rgb(res[2], &colour) == 1)
		return (error("Invalid plane colour", scene->err_m), free(plane),
			free_array(res), 1);
	plane->colour = colour;
	if (add_to_list(&scene->obj_list, plane, PL, plane->colour) == 1)
		return (error("Failed adding plane to the list", scene->err_m),
			free(plane), free_array(res), 1);
	printf("PLANE\n");
	printf("pl point %f %f %f\n", plane->normal.origin.x, plane->normal.origin.y,
		plane->normal.origin.z);
	printf("norm %f %f %f\n", plane->normal.direction.x, plane->normal.direction.y,
		plane->normal.direction.z);
	printf("color %d\n\n", plane->colour);
	return (free_array(res), 0);
}
