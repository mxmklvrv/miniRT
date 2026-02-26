#include "minirt.h"

// 0.0,0.0,20.6 12.6 10,0,255
int	parse_sphere(char *line, t_scene *scene)
{
	char	**res;
	t_sp	*sphere;
	float	diameter;
	int		colour;

	if (count_elements(line) != 3)
		return (error("Invalid specs for sphere", scene->err_m), 1);
	sphere = malloc(sizeof(t_sp));
	if (!sphere)
		return (error(ERR_ALLOC, NULL), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC, NULL), free(sphere), 1);
	if (parse_vector(res[0], &sphere->sp_center, -100.0f, 100.0f) == 1)
		return (error("Invalid sphere center", scene->err_m), free(sphere),
			free_array(res), 1);
	sphere->sp_center.w = 1;//New
	diameter = 0;
	colour = 0;
	if (parse_float(res[1], 0.0f, 100.0f, &diameter) == 1)
		return (error("Invalid sphere diameter", scene->err_m), free(sphere),
			free_array(res), 1);
	if (parse_rgb(res[2], &colour) == 1)
		return (error("Invalid sphere colour", scene->err_m), free(sphere),
			free_array(res), 1);
	sphere->diameter = diameter;
	sphere->colour = colour;
	if (add_to_list(&scene->obj_list, sphere, SP, sphere->colour) == 1)
		return (error("Failed adding sphere to the list", scene->err_m),
			free_array(res), free(sphere), 1);
	printf("SPHERE\n");
	printf("cent %f %f %f\n", sphere->sp_center.x, sphere->sp_center.y,
		sphere->sp_center.z);
	printf("diam %f\n", sphere->diameter);
	printf("color %d\n\n", sphere->colour);
	return (free_array(res), 0);
}
