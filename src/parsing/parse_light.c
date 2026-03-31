#include "minirt.h"

static int init_light(t_light *light, char **res, t_scene *scene);

//int	parse_light(char *line, t_scene *scene)
//{
//	char	**res;
//	float	bright;
//	int		color;

//	if (scene->qt_light > 1)
//		return (error_return(ERR_LIGT_QTY, NULL));
//	if (count_elements(line) != 3)
//		return (error_return(ERR_LIGT_SPEC, scene->error_line));
//	res = ft_split(line, ' ');
//	if (!res)
//		return (error_return(ERR_ALLOC, NULL));
//	bright = 0.0f;
//	color = 0;
//	scene->light.pos.w = 1;
//	if (parse_vector(res[0], &scene->light.pos, -100.0f, 100.0f) == 1)
//		return (parse_error(scene, ERR_LIGT_POS, res, NULL));
//	if (parse_float(res[1], 0.0f, 1.0f, &bright) == 1)
//		return (parse_error(scene, ERR_LIGT_BRIT, res, NULL));
//	if (parse_rgb(res[2], &color) == 1)
//		return (parse_error(scene, ERR_LIGT_COLOR, res, NULL));
//	scene->light.bright = bright;
//	scene->light.color = new_color(255, 255, 255, 255); // this is for bonus
//	free_array(res);
//	return (0);
//}

// // new function for multiple lights
int	parse_light(char *line, t_scene *scene) // new (need to check parse err)
{
	char	**res;
	t_light *light;

	if (count_elements(line) != 3)
		return (error_return(ERR_LIGT_SPEC, scene->error_line));
	light = ft_calloc(1, sizeof(t_light));
	if(!light)
		return (error_return(ERR_ALLOC, NULL));
	res = ft_split(line, ' ');
	if (!res)
		return (parse_error_l(scene, ERR_ALLOC, NULL, light));
	if (init_light(light, res, scene))
		return(parse_error_l(scene, NULL, res, light));
	if(add_light_to_list(scene, light))
		return(parse_error_l(scene, "error light list", res, light));
	free_array(res);
	return (0);
}

static int init_light(t_light *light, char **res, t_scene *scene) // new
{
	if(parse_vector(res[0], &light->pos, -100.0f, 100.0f))
		return (error_return(ERR_LIGT_POS, scene->error_line));
	light->pos.w = 1;
	if(parse_float(res[1], 0.0f, 1.0f, &light->bright))
		return (error_return(ERR_LIGT_BRIT, scene->error_line));
	if(parse_rgb(res[2], &light->color))
		return (error_return(ERR_LIGT_COLOR, scene->error_line));
	return (0);
}
// new functions up