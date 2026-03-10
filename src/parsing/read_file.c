#include "minirt.h"

/*
int	parse_input_file(char *file, t_scene *scene)
{
	int		fd;
	int		check;
	char	*line;
	char	*trimmed;

	check = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_return("cannot open file for reading", NULL));
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \n");
		free(line);
		if (!trimmed)
		{
			error_msg(ERR_ALLOC, NULL); // add to ft_strtrim this line
			return (parse_fatal(scene, fd));
		}
		scene->err_m = trimmed;
		check = dispatch(trimmed, scene);
		free(trimmed);
		if (check != 0)
			return(parse_fatal(scene, fd));
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
*/

int	parse_input_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_return(ERR_OPEN, NULL));
	line = get_next_line(fd);
	while (line)
	{
        if(parse_line(line, scene))
        {
            free(line);
            return(parse_fatal(scene, fd));
        }
        free(line);
		line = get_next_line(fd);
	}
	if(!scene->obj_list) // test
	{
		printf("There are no objects to draaw\n");
		return(parse_fatal(scene, fd));
	}
	close(fd);
	return (0);
}


int parse_line(char *line, t_scene *scene)
{
    char *trimmed;

    trimmed = ft_strtrim(line, " \n");
    if(!trimmed)
        return(error_return(ERR_ALLOC, NULL));
    scene->err_m = trimmed;
    if(dispatch(trimmed, scene))
    {
        free(trimmed);
        return (1);
    }
    free(trimmed);
    return (0);
}


int	postpars_validation(t_scene *scene)
{
	if(scene->qt_ambiant != 1 && scene->qt_cam != 1 && scene->qt_light != 1)
		return (error_return("Invalid nummber of mandotary objects", NULL));
	if(!scene->obj_list)
		return (error_return("There is nothing to render", NULL));
}