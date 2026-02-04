#include "minirt.h"

// 50.0,0.0,20.6    0.0,0.0,1.0    14.2    21.42   10,0,255
int	parse_cylinder(char *line, t_scene *scene)
{
	char	**res;
	t_cy	*cylinder;
	float	diameter;
	float	height;
	int		colour;

	if (count_elements(line) != 5)
		return (error("Invalid specs for cylinder", scene->err_m), 1);
	cylinder = malloc(sizeof(t_cy));
	if (!cylinder)
		return (error(ERR_ALLOC, NULL), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC, NULL), free(cylinder), 1);
	if (parse_vector(res[0], &cylinder->cy_center, -100.0f, 100.0f) == 1)
		return (error("Invalid coordinates of the center of the cylinder",
				scene->err_m), free(cylinder), free_array(res), 1);
	if (parse_vector(res[1], &cylinder->normal, 0.0f, 1.0f) == 1)
		return (error("Invalid coordinates of the center of the cylinder",
				scene->err_m), free(cylinder), free_array(res), 1);
	diameter = 0.0f;
	height = 0.0f;
	colour = 0;
	if (parse_float(res[2], 0.0f, 100.0f, &diameter) == 1)
		return (error("Invalid cylinder diameter", scene->err_m),
			free(cylinder), free_array(res), 1);
	if (parse_float(res[3], 0.0f, 100.0f, &height) == 1)
		return (error("Invalid cylinder height", scene->err_m), free(cylinder),
			free_array(res), 1);
	if (parse_rgb(res[4], &colour) == 1)
		return (error("Invalid cylinder colour", scene->err_m), free(cylinder),
			free_array(res), 1);
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->colour = colour;
	if (add_to_list(&scene->obj_list, cylinder, CY, cylinder->colour) == 1)
		return (error("Failed adding cylinder to the list", scene->err_m),
			free(cylinder), free_array(res), 1);
	printf("CYLINDR\n");
	printf("cy cent %f %f %f\n", cylinder->cy_center.x, cylinder->cy_center.y,
		cylinder->cy_center.z);
	printf("norm %f %f %f\n", cylinder->normal.x, cylinder->normal.y,
		cylinder->normal.z);
	printf("diam %f\n", cylinder->diameter);
	printf("height %f", cylinder->height);
	printf("color %d\n\n", cylinder->colour);
	free_array(res);
	return (0);
}
