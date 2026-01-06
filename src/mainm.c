#include "minirt.h"

// TODO: pars cam
// TODO: probably after parsing need to check

// below maxim
void	free_array(char **arr);
void	error(char *msg);
int		count_elements(char *line);
int		check_int(char *line, int i);
int		check_float_format(char *line);
int		ft_isspace(char ch);
int		check_rgb_format(char *line);
int		ft_atof(const char *line, float *res);
void	get_whole_part(const char *line, int *i, float *temp, int *overflow);
void	get_fraction_part(const char *line, int *i, float *temp, int *overflow);
int		check_rgb_range(char *line);
int		pars_light(char *line, t_scene *scene);
int		extract_floats(const char *line, t_vec3 *vec3, char flag);
t_vec3	creat_vec3(float x, float y, float z);
int		check_split_res(char **split_res);
int		pars_ambient(char *line, t_scene *scene);
int		ft_atorgb(const char *line);
int		ft_rgbtoint(int transp, int red, int green, int blue);
int		check_float_range(float value, float min_value, float max_value);
int		pars_cam_light(char *line, char ch, t_scene *scene);
int		dispatch(char *line, t_scene *scene);
int		pars_input_file(char *file, t_scene *scene);
bool	rt_file_extension(char *file);
int		confirm_input(int ac, char **av);
void	init_scene(t_scene *scene);

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
int	count_elements(char *line)
{
	int	res;
	int	i;
	int	in_word;

	i = 0;
	in_word = 0;
	res = 0;
	while (line && line[i])
	{
		if (line[i] == ' ')
		{
			in_word = 0;
			i++;
		}
		else if (in_word == 1)
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
int	check_int(char *line, int i)
{
	while (line[i] && line[i] != '\n') // !ft_isspace(line[i])
	{
		if (line[i] == '-' || line[i] == '+')
			i++;
		if (ft_isdigit(line[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

// checks the validity of the float nubmer
// '-' accepted, also '+';
// ony digits before and after '.'
int	check_float_format(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '-' || line[i] == '+')
		i++;
	if (ft_strchr(line, '.') == NULL)
		return (check_int(line, i));
	while (line[i] && line[i] != '.')
	{
		if (ft_isdigit(line[i]) == 0)
			return (error("Float num is not correct"), 1);
		i++;
	}
	i++;
	while (line[i] && ft_isspace(line[i]) != 1)
	{
		if (ft_isdigit(line[i]) == 0)
			return (error("Float number is not correct"), 1);
		i++;
	}
	return (0);
}

int	ft_isspace(char ch)
{
	if ((ch >= 8 && ch <= 13) || ch == 32)
		return (1);
	return (0);
}
// 255,255,255 = 11 || 0,0,0 = 5
// checks rgb format
// creates 2d arr with 3 inputs
int	check_rgb_format(char *line)
{
	char	**rgb;
	int		i;

	rgb = ft_split(line, ',');
	if (!rgb)
		return (error("Wrong format of RGB"), 1);
	i = 0;
	while (i < 3)
	{
		if (!rgb[i])
			return (free_array(rgb), error("Wrong format of RGB"), 1);
		if (check_int(rgb[i], 0))
			return (free_array(rgb), error("Wrong format of RGB"), 1);
		if (check_rgb_range(rgb[i]))
			return (free_array(rgb), error("Out of range for RGB"), 1);
		i++;
	}
	if (rgb[3])
		return (free_array(rgb), error("Wrong format of RGB"), 1);
	free_array(rgb);
	return (0);
}

// ascii to float converter
// detects sign
// if overflow happens, still writes garbage value to res
// returns 0 on success, 1 otherwise
int	ft_atof(const char *line, float *res)
{
	int		sign;
	int		i;
	float	temp;
	int		overflow;

	i = 0;
	sign = 1;
	temp = 0.0f;
	overflow = 0;
	if (line[i] == '-' || line[i] == '+')
	{
		if (line[i] == '-')
			sign *= -1;
		i++;
	}
	get_whole_part(line, &i, &temp, &overflow);
	get_fraction_part(line, &i, &temp, &overflow);
	*res = temp * sign;
	return (overflow);
}
// part of ft_atof function.
// gets the whole part of float num (before '.')
// modifies passed params
void	get_whole_part(const char *line, int *i, float *temp, int *overflow)
{
	while (ft_isdigit(line[*i]))
	{
		*temp = *temp * 10 + (line[*i] - '0');
		if (*temp > __FLT_MAX__) // for now, need to define by myself mb
			*overflow = 1;
		(*i)++;
	}
}
// part of ft_atof function.
// gets the fractional part of float num (after '.')
// modifies passed params
void	get_fraction_part(const char *line, int *i, float *temp, int *overflow)
{
	float	fraction;

	fraction = 0.1f;
	if (line[*i] == '.')
		(*i)++;
	while (ft_isdigit(line[*i]))
	{
		*temp += (line[*i] - '0') * fraction;
		fraction *= 0.1f;
		if (*temp > __FLT_MAX__) // for now, need to define by myself mb
			*overflow = 1;
		(*i)++;
	}
}

// checks if num is in 0-255 rage
int	check_rgb_range(char *line)
{
	int	val;

	if (!line)
		return (1);
	val = ft_atoi(line);
	if (val < 0 || val > 255)
		return (1);
	return (0);
}
// <-40.0,50.0,0.0     0.6     10,0,255>
int	pars_light(char *line, t_scene *scene)
{
	char	**res;

	res = NULL;                    // might remove this
	if (count_elements(line) != 3) // mb 2 for mand. part, for now 3
		return (error("Wrong specs for light"), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), 1);
	// int i = 0;
	// while(res[i])
	// {
	// 	printf("%s", res[i]);
	// 	i++;
	// }
	// add light linked list to the front, seems we will have more than that.
	// should we ??
	// get floats as a vector.
	if (extract_floats(res[0], &scene->light.pos, 'M'))
	{
		free_array(res);
		return (1);
	}
	if (check_float_format(res[1]) == 1)
	{
		free_array(res);
		return (1);
	}
	if (ft_atof(res[1], &scene->light.bright) == 1)
	{
		free_array(res);
		return (1);
	}
	if (check_float_range(scene->light.bright, 0.0f, 1.0f) == 1)
	{
		free_array(res);
		return (1);
	}
	if (check_rgb_format(res[2]) == 0)
		scene->light.color = ft_atorgb(res[2]);
	else
		return (free_array(res), 1);
	return (free_array(res), 0);
}

//  <-50.0,0,20 0,0,1 70>
int	pars_cam(char *line, t_scene *scene)
{
	char	**res;

	res = NULL;
	if (count_elements(line) != 3)
		return (error("Wrong specs for cam"), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), 1);
	if (extract_floats(res[0], &scene->cam.view_point, 'M'))
	{
		free_array(res);
		return (1);
	}
	if (extract_floats(res[1], &scene->cam.orient, 'N'))
	{
		free_array(res);
		return (1);
	}
	if (check_float_format(res[2]) == 1)
	{
		free_array(res);
		return (1);
	}
	if (ft_atof(res[2], &scene->cam.fov) == 1)
	{
		free_array(res);
		return (1);
	}
	if (check_float_range(scene->cam.fov, 0.0f, 180.0f) == 1)
	{
		free_array(res);
		return (1);
	}
	free_array(res);
	return (0);
}

// [-40.0][50.0][0.0]
int	extract_floats(const char *line, t_vec3 *vec3, char flag)
{
	char	**res;
	float	x;
	float	y;
	float	z;

	res = ft_split(line, ',');
	if (!res)
		return (error(ERR_ALLOC), 1);
	if (check_split_res(res) == 1)
		return (error("wrong float format"), 1);
	x = 0;
	y = 0;
	z = 0;
	if (ft_atof(res[0], &x) == 1 || ft_atof(res[1], &y) == 1 || ft_atof(res[2],
			&z) == 1)
		return (free_array(res), error("float overflow"), 1);
	if (flag == 'N')
	{
		if (check_float_range(x, -1.0f, 1.0f) == 1 || check_float_range(y,
				-1.0f, 1.0f) == 1 || check_float_range(z, -1.0f, 1.0f) == 1)
			return (free_array(res), 1);
	}
	*vec3 = creat_vec3(x, y, z);
	free_array(res);
	return (0);
}

t_vec3	creat_vec3(float x, float y, float z)
{
	t_vec3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

// function which confirms that we got exactly
// 3 non empty arrays with valid float format nums
int	check_split_res(char **split_res)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!split_res[i])
			return (1);
		if (check_float_format(split_res[i]) == 1)
			return (1);
		i++;
	}
	if (split_res[3])
		return (1);
	return (0);
}

// [0.0 - 1.0] [0-255]  <0,2 255,255,255>
// main parsing ambient light function
int	pars_ambient(char *line, t_scene *scene)
{
	char	**res;

	res = NULL;
	if (count_elements(line) != 2)
		return (error("Wrong ambient specs"), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), 1);
	if (check_float_format(res[0]) == 1)
		return (free_array(res), 1);
	if (check_rgb_format(res[1]) == 1)
		return (free_array(res), 1);
	if (ft_atof(res[0], &scene->ambient.amb))
		return (free_array(res), 1);
	if (check_float_range(scene->ambient.amb, 0.0f, 1.0f) == 1)
		return (free_array(res), 1);
	scene->ambient.colour = ft_atorgb(res[1]);
	free_array(res);
	return (0);
}
// converting ascii to rgb values
int	ft_atorgb(const char *line)
{
	int	i;
	int	red;
	int	green;
	int	blue;

	i = 0;
	red = ft_atoi(line);
	while (line[i] && line[i] != ',')
		i++;
	i++;
	green = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	i++;
	blue = ft_atoi(line + i);
	return (ft_rgbtoint(255, red, green, blue));
}
// with bitshifting storing rgb into singl int
// t - transparency (always to max value = 255)
int	ft_rgbtoint(int transp, int red, int green, int blue)
{
	return (transp << 24 | red << 16 | green << 8 | blue);
}

// Function which confirms the range of the float num
// min_value == min possible starting value
// max-value == max possible ending value
// returns 0 on success, 1 otherwise
int	check_float_range(float value, float min_value, float max_value)
{
	if (min_value <= value && value <= max_value)
		return (0);
	return (error("Range of float is not correect"), 1);
}

// if ch == C -> pars_cam
// if ch == L -> pars_lignt
// if ch == A -> pars_ambient
// need to know that we have 1 of each, else, err
int	pars_cam_light(char *line, char ch, t_scene *scene)
{
	if (ch == 'C')
	{
		scene->qt_cam++;
		return (pars_cam(++line, scene));
	}
	else if (ch == 'A')
	{
		scene->qt_ambiant++;
		return (pars_ambient(++line, scene));
	}
	else if (ch == 'L')
	{
		scene->qt_light++;
		return (pars_light(++line, scene));
	}
	// we need a func to count CAL at the end of pars
	return (0);
}

// checks the first meaningful char(s) in the line.
// if found, goes to corresponding function
int	dispatch(char *line, t_scene *scene)
{
	while (*line == ' ') // what about tabs here ??
		line++;
	if (*line == '\0' || *line == '\n') // what else is ok
		return (0);
	else if (ft_strchr("CAL", *line))
		return (pars_cam_light(line, *line, scene));
	// else if (ft_strncmp(line, "sp", 2) == 0)
	// 	return (pars_sphere());
	// else if (ft_strncmp(line, "cy", 2) == 0)
	// 	return (pars_cylinder());
	// else if (ft_strncmp(line, "pl", 2) == 0)
	// 	return (pars_plane());
	else
		return (error("Unknown char detected in .rt"), 1);
}

int	pars_input_file(char *file, t_scene *scene)
{
	int		fd;
	int		check;
	char	*line;

	check = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("cannot open file for reading"), 1);
	line = get_next_line(fd);
	while (line)
	{
		check = dispatch(line, scene);
		if (check != 0)
		{
			close(fd);
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
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
	return (0);
}

void	init_scene(t_scene *scene)
{
	scene->mlx = NULL;
	scene->window = NULL;
	scene->obj_list = NULL;
	// scene->light = NULL;
}

int	main(int ac, char **av)
{
	t_scene	scene;

	init_scene(&scene);
	if (confirm_input(ac, av) == 1)
	{
		// free scene and everything
		return (EXIT_FAILURE);
	}
	if (pars_input_file(av[1], &scene) == 1)
	{
		return (EXIT_FAILURE);
	}
	printf("amb: float amb: %f, int colour: %d\n", scene.ambient.amb,
		scene.ambient.colour);
	printf("light: float bright: %f, int colour: %d,vector pos x = % f y = %f z = %f\n", scene.light.bright, scene.light.color, scene.light.pos.x,
		scene.light.pos.y, scene.light.pos.z);
	printf("Cam: FOV: %f, VP_x: %f, VP_y: %f, VP_z: %f, OV_x: %f, OV_y: %f,OV_z: %f\n", scene.cam.fov, scene.cam.view_point.x,
		scene.cam.view_point.y, scene.cam.view_point.z, scene.cam.orient.x,
		scene.cam.orient.y, scene.cam.orient.z);
	return (0);
}
