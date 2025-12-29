#include "minirt.h"

// below maxim

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}


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
// checks the validity of int
int check_int(char *line, int i)
{
    while(line[i])
    {
        if(ft_isdigit(line[i]) == 0)
            return ("An int num is not correct", 1);
        i++;
    }
    return (0);
}


// checks the validity of the float nubmer
// '-' accepted
// ony digits before and after '.'
int check_float_format(char *line)
{
    int i;

    i = 0;
    if(line[i] == '-')
        i++;
    if(ft_strchr(line, '.') == NULL)
        return (check_int(line, i));
    while(line[i] && line[i] != '.')
    {
        if(ft_isdigit(line[i]) == 0)
            return (error("Float num is not correct"), 1);
    }
    i++;
    while(line[i] && ft_isspace(line[i]) != 1)
    {
        if(ft_isdigit(line[i]) == 0)
            return (error("Float number is not correct"), 1);
            i++;
    }
    return (0);
}

int ft_isspace(char ch)
{
    if((ch >= 8 && ch <= 13) || ch == 32)
        return (1);
    return (0);
}
//255,255,255 = 11 || 0,0,0 = 5
// checks rgb format
// creates 2d arr with 3 inputs
int check_rgb_format(char *line)
{
    char **rgb;
    int i;

    rgb = ft_split(line, ',');
    if(!rgb)
        return(error("Wrong format of RGB"), 1);
    i = 0;
    while(i < 3)
    {
        if(!rgb[i])
            return(free_array(rgb),error("Wrong format of RGB"), 1);
        if(check_int(rgb[i], 0))
            return(free_array(rgb),error("Wrong format of RGB"), 1);
        if (check_rgb_range(rgb[i]))
            return(free_array(rgb),error("Out of range for RGB"), 1);
        i++;
    }
    if(rgb[3])
        return(free_array(rgb),error("Wrong format of RGB"), 1);
    free_array(rgb);
}

// checks if num is in 0-255 rage
int check_rgb_range(char *line)
{
    int val;

    if(!line)
        return (1);
    val = ft_atoi(line);
    if(val < 0 || val > 255)
        return(error("Out of range for RGB"), 1);
    return (0);
}

// [0.0 - 1.0] [0-255]  <0,2 255,255,255>
// floats 

int pars_ambient(char *line, t_scene *scene)
{
    char **res;

    res = NULL;
    if(count_elements(line) != 2)
        return (1);
    res = ft_split(' '); // 
    if(!res)
        return(ERR_ALLOC, 1);
    // rgb  and floats format confirmation 
    if (check_float_format(res[0]) == 1|| check_rgb(res[1]) == 1)
        return(free(res), 1); 
    //floats range confiramtion
    if (check_float_range() == 1)
    

}


// if ch == C -> pars_cam
// if ch == L -> pars_lignt
// if ch == A -> pars_ambient
// need to know that we have 1 of each, else, err
int pars_cam_light(char *line, char ch, t_scene *scene)
{
    if(ch == 'C')
    {
        scene->qt_cam++;
        return(pars_cam(++line, scene));
    }
    else if(ch == 'A')
    {
        scene->qt_ambiant++;
        return(pars_ambient(++line, scene));
    }
    else if(ch == 'L')
    {
        scene->qt_light++;
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
        return (pars_cylinder());
    else if (ft_strncmp(line, "pl", 2) == 0)
        return (pars_plane());
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
    // another func to check amb/cam/light
    // should have qty == 1 of each.

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
