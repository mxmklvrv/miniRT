#include "minirt.h"

// below maxim

void	error(char *msg)
{
	ft_putendl_fd(ERR_MSG, 2);
	ft_putendl_fd(msg, 2);
}

// checks how many elements in the string
int count_elements(char line)
{
    int res;
    int i;
    int in_word;

    i = 0;
    in_word = 0;
    res = 0;
    while(line && line[i])
    {
        if(line[i] == ' ')
        {
            in_word = 0;
            i++;
        }
        else if(in_word == 1)
            i++;
        else
        {
            in_word = 1;
            res++;
            i++;
        }
    }
    return (res);
}


int pars_ambient(char *line, t_scene scene)
{
    if(count_elements(line) != 2)
        return (1);

}


// if ch == C -> pars_cam
// if ch == L -> pars_lignt
// if ch == A -> pars_ambient
// need to know that we have 1 of each, else, err
int pars_cam_light(char *line, char ch, t_scene scene)
{
    int cam; // need to safe qty 
    int amb; // either make it static (not sure if ok)
    int light; // or add to struct scene (makes sense atm)

    if(ch == 'C')
    {
        cam++;
        return(pars_cam(++line, scene));
    }
    else if(ch == 'A')
    {
        amb++;
        return(pars_ambient(++line, scene));
    }
    else if(ch == 'L')
    {
        light++;
        return(pars_light(++line, scene));
    }
}

// checks the first meaningful char(s) in the line. 
// if found, goes to corresponding function
int dispatch(char *line, t_scene *scene)
{
    while(*line == ' ') // what about tabs here ?? 
        line++;
    if(*line == '\0' || *line == '\n') // what else is ok, like comments or smth.. 
        return (0);
    else if(ft_strchr("CAL", *line))
        return (pars_cam_light(line, *line, scene));
    else if(ft_strncmp(line, "sp", 2) == 0)
        return (pars_sphere());
    else if (ft_strncmp(line, "cy", 2) == 0)
        return (pars_cylinder);
    else if (ft_strncmp(line, "pl", 2) == 0)
        return (pars_plane);
    else
        return(error("Unknown char detected in .rt"), 1);
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

int	confirm_input(int ac, char **av)
{
	if (ac != 2)
		return (error(ERR_AC), 1);
	if (!rt_file_extension(av[1]))
		return (error(ERR_EXT), 1);
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
    
	if (confirm_input(ac, av) == 1 || pars_input_file(av[1], &scene) == 1)
    {
        // free scene and everything 
        return(EXIT_FAILURE);
    }
}
