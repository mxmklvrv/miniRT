
#include "minirt.h"

// int	parse_cam(char *line, t_scene *scene)
// {
// 	char	**res;
// 	float	fov;

// 	if (scene->qt_cam > 1)
// 		return (error_return(ERR_CAM_QTY, scene->err_m));
// 	if (count_elements(line) != 3)
// 		return (error_return(ERR_CAM_SPEC, scene->err_m));
// 	res = ft_split(line, ' ');
// 	if (!res)
// 		return (error_return(ERR_ALLOC, NULL));
// 	if (parse_vector(res[0], &scene->cam.orient.origin, -100.0f, 100.0f) == 1)
// 	{
// 		free_array(res);
// 		return(error_return(ERR_CAM_VIEW, scene->err_m));
// 	}
// 	scene->cam.orient.origin.w = 1;
// 	if (parse_vector(res[1], &scene->cam.orient.direction, 0.0f, 1.0f) == 1)
// 	{
// 		free_array(res);
// 		return (error_return(ERR_CAM_ORIT, scene->err_m));
// 	}
// 	scene->cam.orient.direction.w = 0;
// 	fov = 0;
// 	if (parse_float(res[2], 0.0f, 180.0f, &fov) == 1)
// 	{
// 		free_array(res);
// 		return (error_return(ERR_CAM_FOV, scene->err_m));
// 	}
// 	scene->cam.fov = fov;
// 	free_array(res);
// 	return (0);
// }

int	parse_cam(char *line, t_scene *scene)
{
	char	**res;
	float	fov;

	if (scene->qt_cam > 1)
		return (error_return(ERR_CAM_QTY, scene->err_m));
	if (count_elements(line) != 3)
		return (error_return(ERR_CAM_SPEC, scene->err_m));
	res = ft_split(line, ' ');
	if (!res)
		return (error_return(ERR_ALLOC, NULL));
	if (parse_vector(res[0], &scene->cam.orient.origin, -100.0f, 100.0f) == 1)
		return (parse_error(scene, ERR_CAM_VIEW, res, NULL));
	scene->cam.orient.origin.w = 1;
	if (parse_vector(res[1], &scene->cam.orient.direction, 0.0f, 1.0f) == 1)
		return (parse_error(scene, ERR_CAM_ORIT, res, NULL));
	scene->cam.orient.direction.w = 0;
	fov = 0;
	if (parse_float(res[2], 0.0f, 180.0f, &fov) == 1)
		return (parse_error(scene, ERR_CAM_FOV, res, NULL));
	scene->cam.fov = fov;
	free_array(res);
	return (0);
}

