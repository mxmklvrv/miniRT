#include "minirt.h"

// below maxim

void	error(char *msg)
{
	ft_putendl_fd(ERR_MSG, 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE); // will remove 
}

int dispatch(char *line, t_scene *scene)
{
    while(*line == ' ')
        line++;
    if(*line == '\0' || *line == '\n')
        return (0);
    // check for A C L PL CY SP etc
}

int 	pars_input_file(char *file, t_scene *scene)
{
    int     fd;
    int     check;
    char    *line;

    check = 1;
    fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("cannot open file for reading"), 1);
    line = get_next_line(fd);
    while(line)
    {
        check = dispatch(line, scene);
        if(check != 0)
        {
            close(fd);
            free(line);
            return(1) // fail
        }       
    }

}


bool	rt_file_extension(char *file)
{
	size_t	len;

	if (!file)
		return (false);
	len = ft_strlen(file);
	if (len < 3)
		return (false);
	if (ft_strncmp(file + len - 3, ".rt", 3) != 0)
		return (false);
	return (true);
}

void	confirm_input(int ac, char **av)
{
	if (ac != 2)
		error(ERR_AC);
	if (!rt_file_extension(av[1]))
		error(ERR_EXT);
}

void    init_scene(t_scene *scene)
{
    scene->mlx = NULL;
    scene->window = NULL;
    scene->obj_list = NULL;
}

int	main(int ac, char **av)
{
	t_scene scene;

	
    init_scene(&scene);
    confirm_input(ac, av);
	if (pars_input_file(av[1], &scene) == 1)
    {
        // free scene and everything 
        return(EXIT_FAILURE);
    }
}
