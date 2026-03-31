#include "minirt.h"

int	parse_error(t_scene *scene, char *msg, char **res, t_shape *shape)
{
	if (msg)
		error_msg(msg, scene->error_line);
	if (res)
		free_array(res);
	if (shape)
		free(shape);
	return (1);
}
// new for multiple lights
int	parse_error(t_scene *scene, char *msg, char **res, void *ptr)
{
	if (msg)
		error_msg(msg, scene->error_line);
	if (res)
		free_array(res);
	if (ptr)
		free(ptr);
	return (1);
}
// new up 

int	parse_fatal(t_scene *scene, int fd)
{
	if (fd >= 0)
		close(fd);
	free_scene(scene);
	return (1);
}

int	error_return(char *msg, char *line)
{
	error_msg(msg, line);
	return (1);
}

void	error_msg(char *msg, char *line)
{
	ft_putendl_fd(ERR_MSG, 2);
	ft_putendl_fd(msg, 2);
	if (line != NULL)
		ft_printf("Problem in line: %s\n", line);
}
