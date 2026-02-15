#include "minirt.h"

int	parse_input_file(char *file, t_scene *scene)
{
	int		fd;
	int		check;
	char	*line;
	char	*trimmed;

	check = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("cannot open file for reading", NULL), 1);
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \n");
		free(line);
		if (!trimmed)
		{
			close(fd);
			return (error(ERR_ALLOC, NULL), 1);
		}
		scene->err_m = trimmed;
		check = dispatch(trimmed, scene);
		free(trimmed);
		if (check != 0)
		{
			close(fd);
			return (1);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
