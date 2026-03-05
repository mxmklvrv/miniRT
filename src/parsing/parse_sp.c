#include "minirt.h"

// 0.0,0.0,20.6 12.6 10,0,255
// !!!!!!!!!!!!!!!! DIRTY VERSION FOR TESTS !!!!!!!!!!!!!!!!!!!!!!!!!!
// int	parse_sphere(char *line, t_scene *scene)
// {
// 	char	**res;
// 	t_sp	*sphere;
// 	float	diameter;
// 	int		colour;

// 	if (count_elements(line) != 3)
// 		return (error("Invalid specs for sphere", scene->err_m), 1);
// 	sphere = malloc(sizeof(t_sp));
// 	if (!sphere)
// 		return (error(ERR_ALLOC, NULL), 1);
// 	res = ft_split(line, ' ');
// 	if (!res)
// 		return (error(ERR_ALLOC, NULL), free(sphere), 1);
// 	if (parse_vector(res[0], &sphere->sp_center, -100.0f, 100.0f) == 1)
// 		return (error("Invalid sphere center", scene->err_m), free(sphere),
// 			free_array(res), 1);
// 	sphere->sp_center.w = 1;//New
// 	diameter = 0;
// 	colour = 0;
// 	if (parse_float(res[1], 0.0f, 100.0f, &diameter) == 1)
// 		return (error("Invalid sphere diameter", scene->err_m), free(sphere),
// 			free_array(res), 1);
// 	if (parse_rgb(res[2], &colour) == 1)
// 		return (error("Invalid sphere colour", scene->err_m), free(sphere),
// 			free_array(res), 1);
// 	sphere->diameter = diameter;
// 	sphere->colour = colour;
// 	if (add_to_list(&scene->obj_list, sphere, SP, sphere->colour) == 1)
// 		return (error("Failed adding sphere to the list", scene->err_m),
// 			free_array(res), free(sphere), 1);
// 	printf("SPHERE\n");
// 	printf("cent %f %f %f\n", sphere->sp_center.x, sphere->sp_center.y,
// 		sphere->sp_center.z);
// 	printf("diam %f\n", sphere->diameter);
// 	printf("color %d\n\n", sphere->colour);
// 	return (free_array(res), 0);
// }


// new version for shape
int	parse_sphere(char *line, t_scene *scene)
{
	char	**res;
	t_shape	*shape;

	if (count_elements(line) != 3)
		return (error("Invalid specs for sphere", scene->err_m), 1);
	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (error(ERR_ALLOC, NULL), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC, NULL), free(shape), 1);
	if(init_sphere(shape, res, scene))
		return (free(shape), free_array(res), 1);
	if (add_to_list(&scene->obj_list, shape) == 1)
		return (error("Failed adding sphere to the list", scene->err_m),
			free_array(res), free(shape), 1);
	return (free_array(res), 0);
}

int init_sphere(t_shape *shape, char **res, t_scene *scene)
{
	shape->obj_type = SP;
	shape->center.w = 1;
	if (parse_vector(res[0], &shape->center, -100.0f, 100.0f))
		return (error("Invalid sphere center", scene->err_m), 1);
	if (parse_float(res[1], 0.0f, 100.0f, &shape->diameter))
		return (error("Invalid sphere diameter", scene->err_m), 1);
	if (parse_rgb(res[2], &shape->colour))
		return (error("Invalid sphere colour", scene->err_m), 1);
	return (0);
}

