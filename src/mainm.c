#include "minirt.h"

// TODO: probably after parsing
/**
 * 1. scene lvl validation:
 * -1 cam 1 amb 1 light
 * - at list 1 object probably
 * 2. obj lvl validation:
 * - no trash values
 * - no zeros
 * Sphere
 *
 *
 * */

int		add_to_list(t_olist **list, void *object, t_otype type, int colour);
void	free_list(t_olist *list);
t_vec3	creat_vec3(float x, float y, float z);
void	free_array(char **arr);
void	error(char *msg);
int		count_elements(char *line);
int		is_valid_int(char *line);
int		is_valid_float(char *line);
int		ft_isspace(char ch);
int		is_valid_comas(const char *line);
int		ft_rgbtoint(int transp, int red, int green, int blue);
int		ft_atof(const char *line, float *res);
void	get_whole_part(const char *line, int *i, float *temp, int *overflow);
void	get_fraction_part(const char *line, int *i, float *temp, int *overflow);
int		parse_rgb(char *str, int *color);
int		parse_vector(char *str, t_vec3 *vector, float min, float max);
int		parse_int(char *str, int min, int max, int *res);
int		parse_float(char *str, float min, float max, float *res);
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);
int		parse_ambient(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);
int		parse_cam(char *line, t_scene *scene);
int		pars_cam_light(char *line, char ch, t_scene *scene);
int		dispatch(char *line, t_scene *scene);
int		pars_input_file(char *file, t_scene *scene);
bool	rt_file_extension(char *file);
int		confirm_input(int ac, char **av);
void	init_scene(t_scene *scene);
void	kill_all(t_scene *scene);

// test functions
void	print_vars(t_scene *scene);
void	print_list(t_scene *scene);

//
/*
// below maxim
void	free_array(char **arr);
void	error(char *msg);
int		count_elements(char *line);
// int		check_int(char *line, int i);
// int		check_float_format(char *line);
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
int		is_valid_comas(const char *line);



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
	if (extract_floats(res[0], &scene->light.pos, 'M'))
	{
		free_array(res);
		return (1);
	}
	if (is_valid_float(res[1]) == 1)
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
	if (is_valid_float(res[2]) == 1)
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
		if (is_valid_float(split_res[i]) == 1)
			return (1);
		i++;
	}
	if (split_res[3])
		return (1);
	return (0);
}



// Function which confirms the range of the float num
// min_value == min possible starting value
// max-value == max possible ending value
// returns 0 on success, 1 otherwise
int	check_float_range(float value, float min_value, float max_value)
{
	if (min_value <= value && value <= max_value)
		return (0);
	return (1);
}



// [-40.0][50.0][0.0]
int	extract_floats(const char *line, t_vec3 *vec3, char flag)
{
	char	**res;

	if(is_valid_comas(line)== 1)
		return (error("wrong float format"), 1);
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

// 255,255,255 = 11 || 0,0,0 = 5
// checks rgb format
// creates 2d arr with 3 inputs
int	check_rgb_format(char *line)
{
	char	**rgb;
	int		i;

	if (is_valid_comas(line) == 1)
		return (error("Wrong format of RGB"), 1);
	rgb = ft_split(line, ',');
	if (!rgb)
		return (error("Wrong format of RGB"), 1);
	i = 0;
	while (i < 3)
	{
		if (!rgb[i] || rgb[i][0] == '\0')
			return (free_array(rgb), error("Wrong format of RGB"), 1);
		if (is_valid_int(rgb[i]))
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


// [0.0 - 1.0] [0-255]
// main parsing ambient light function
// new version
int	pars_ambient(char *line, t_scene *scene)
{
	char	**res;

	res = NULL;
	if (count_elements(line) != 2)
		return (error("Wrong ambient specs"), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), 1);
	if(is_valid_float(res[0]) == 1 || ft_atof(res[0],&scene->ambient.amb) == 1)
		return (error("Invalid ambient ratio"),free_array(res), 1);
	if(check_float_range(scene->ambient.amb, 0.0f, 1.0f) == 1)
		return (error("Ambient ratio out of range [0,1]")free_array(res), 1);
	if(check_rgb_format(res[1]) == 1)
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

*/

//////////////////////////////////////////////////////////////////////////////////////////////////
// STEP 5: Helper functions

void	kill_all(t_scene *scene)
{
	free_list(scene->obj_list);
}

int	add_to_list(t_olist **list, void *object, t_otype type, int colour)
{
	t_olist	*new;
	t_olist	*temp;

	new = malloc(sizeof(t_olist));
	if (!new)
		return (1);
	new->obj_type = type;
	new->obj = object;
	new->colour = colour;
	new->next = NULL;
	// id ??
	if (*list == NULL)
		*list = new;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

void	free_list(t_olist *list)
{
	t_olist	*temp;

	if (!list)
		return ;
	while (list)
	{
		temp = list->next;
		if (list->obj)
			free(list->obj);
		free(list);
		list = temp;
	}
	list = NULL;
}

t_vec3	creat_vec3(float x, float y, float z)
{
	t_vec3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

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

int	is_valid_int(char *line)
{
	int	i;

	i = 0;
	if (!line || line[0] == '\0')
		return (1);
	if (line[i] == '+' || line[i] == '-')
		i++;
	if (ft_isdigit(line[i]) == 0)
		return (1);
	while (ft_isdigit(line[i]) == 1)
		i++;
	if (line[i] != '\0' && line[i] != '\n')
		return (1);
	return (0);
}
// checks the validity of the float nubmer
// '-' accepted, also '+';
// ony digits before and after '.'
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!0. fixe

int	is_valid_float(char *line)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (line[i] == '-' || line[i] == '+')
		i++;
	if (ft_isdigit(line[i]) == 0)
		return (1);
	while (line[i])
	{
		if (line[i] == '.')
		{
			if (dot == 1)
				return (1);
			dot = 1;
		}
		else if (ft_isdigit(line[i]) == 0)
			return (1);
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

int	is_valid_comas(const char *line)
{
	int	i;
	int	coma;

	i = 0;
	coma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			coma++;
		i++;
	}
	if (coma != 2)
		return (1);
	return (0);
}

// with bitshifting storing rgb into singl int
// t - transparency (always to max value = 255)
int	ft_rgbtoint(int transp, int red, int green, int blue)
{
	return (transp << 24 | red << 16 | green << 8 | blue);
}

// ascii to float converter
// detects sign
// if overflow happens, still writes garbage value to res
// returns 0 on success, 1 otherwise
// might need to make res = 0;
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

int	parse_rgb(char *str, int *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (!str || is_valid_comas(str))
		return (1);
	rgb = ft_split(str, ',');
	if (!rgb)
		return (error(ERR_ALLOC), 1);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_array(rgb), 1);
	r = 0;
	g = 0;
	b = 0;
	if (parse_int(rgb[0], 0, 255, &r) == 1 || parse_int(rgb[1], 0, 255, &g) == 1
		|| parse_int(rgb[2], 0, 255, &b) == 1)
		return (free_array(rgb), 1);
	*color = ft_rgbtoint(255, r, g, b);
	free_array(rgb);
	return (0);
}

int	parse_vector(char *str, t_vec3 *vector, float min, float max)
{
	char	**res;
	float	x;
	float	y;
	float	z;

	if (!str || is_valid_comas(str) == 1)
		return (1);
	res = ft_split(str, ',');
	if (!res)
		return (error(ERR_ALLOC), 1);
	if (!res[0] || !res[1] || !res[2] || res[3])
		return (free_array(res), 1);
	x = 0;
	y = 0;
	z = 0;
	if (parse_float(res[0], min, max, &x) == 1 || parse_float(res[1], min, max,
			&y) == 1 || parse_float(res[2], min, max, &z) == 1)
		return (free_array(res), 1);
	*vector = creat_vec3(x, y, z);
	free_array(res);
	return (0);
}

int	parse_int(char *str, int min, int max, int *res)
{
	int	temp;

	temp = 0;
	if (!str || is_valid_int(str) == 1)
		return (1);
	temp = ft_atoi(str);
	if (temp < min || temp > max)
		return (1);
	*res = temp;
	return (0);
}

int	parse_float(char *str, float min, float max, float *res)
{
	if (!str || is_valid_float(str) == 1)
		return (1);
	if (ft_atof(str, res))
		return (1);
	if (*res < min || *res > max)
		return (1);
	return (0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
// STEP 4: Main parsing functions for sphere cylinder plane
// Extracting basic data
// Adding each to the linked list of objects

// 0.0,0.0,20.6 12.6 10,0,255
int	parse_sphere(char *line, t_scene *scene)
{
	char	**res;
	t_sp	*sphere;
	float	diameter;
	int		colour;

	if (count_elements(line) != 3)
		return (error("Invalid specs for sphere"), 1);
	sphere = malloc(sizeof(t_sp));
	if (!sphere)
		return (error(ERR_ALLOC), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), free(sphere), 1);
	if (parse_vector(res[0], &sphere->sp_center, -100.0f, 100.0f) == 1)
		return (error("Invalid sphere center"), free(sphere), free_array(res),
			1);
	diameter = 0;
	colour = 0;
	if (parse_float(res[1], 0.0f, 100.0f, &diameter) == 1)
		return (error("Invalid sphere diameter"), free(sphere), free_array(res),
			1);
	if (parse_rgb(res[2], &colour) == 1)
		return (error("Invalid sphere colour"), free(sphere), free_array(res),
			1);
	sphere->diameter = diameter;
	sphere->colour = colour;
	if (add_to_list(&scene->obj_list, sphere, SP, sphere->colour) == 1)
		return (error("Failed adding sphere to the list"), free_array(res),
			free(sphere), 1);
	printf("SPHERE\n");
	printf("cent %f %f %f\n", sphere->sp_center.x, sphere->sp_center.y,
		sphere->sp_center.z);
	printf("diam %f\n", sphere->diameter);
	printf("color %d\n\n", sphere->colour);
	return (free_array(res), 0);
}

// 0.0,0.0,-10.0  0.0,1.0,0.0  0,0,225
int	parse_plane(char *line, t_scene *scene)
{
	char	**res;
	t_pl	*plane;
	int		colour;

	if (count_elements(line) != 3)
		return (error("Invalid specs for plane"), 1);
	plane = malloc(sizeof(t_pl));
	if (!plane)
		return (error(ERR_ALLOC), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), free(plane), 1);
	if (parse_vector(res[0], &plane->pl_point, -100.0f, 100.0f) == 1)
		return (error("Invalid coordinates of a point in plane"), free(plane),
			free_array(res), 1);
	if (parse_vector(res[1], &plane->normal, 0.0f, 1.0f) == 1)
		return (error("Invalid normal vector for plane"), free(plane),
			free_array(res), 1);
	colour = 0;
	if (parse_rgb(res[2], &colour) == 1)
		return (error("Invalid plane colour"), free(plane), free_array(res), 1);
	plane->colour = colour;
	if (add_to_list(&scene->obj_list, plane, PL, plane->colour) == 1)
		return (error("Failed adding plane to the list"), free(plane),
			free_array(res), 1);
	printf("PLANE\n");
	printf("pl point %f %f %f\n", plane->pl_point.x, plane->pl_point.y,
		plane->pl_point.z);
	printf("norm %f %f %f\n", plane->normal.x, plane->normal.y,
		plane->normal.z);
	printf("color %d\n\n", plane->colour);
	return (free_array(res), 0);
}
// 50.0,0.0,20.6    0.0,0.0,1.0    14.2    21.42   10,0,255
int	parse_cylinder(char *line, t_scene *scene)
{
	char	**res;
	t_cy	*cylinder;
	float	diameter;
	float	height;
	int		colour;

	if (count_elements(line) != 5)
		return (error("Invalid specs for cylinder"), 1);
	cylinder = malloc(sizeof(t_cy));
	if (!cylinder)
		return (error(ERR_ALLOC), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), free(cylinder), 1);
	if (parse_vector(res[0], &cylinder->cy_center, -100.0f, 100.0f) == 1)
		return (error("Invalid coordinates of the center of the cylinder"),
			free(cylinder), free_array(res), 1);
	if (parse_vector(res[1], &cylinder->normal, 0.0f, 1.0f) == 1)
		return (error("Invalid coordinates of the center of the cylinder"),
			free(cylinder), free_array(res), 1);
	diameter = 0.0f;
	height = 0.0f;
	colour = 0;
	if (parse_float(res[2], 0.0f, 100.0f, &diameter) == 1)
		return (error("Invalid cylinder diameter"), free(cylinder),
			free_array(res), 1);
	if (parse_float(res[3], 0.0f, 100.0f, &height) == 1)
		return (error("Invalid cylinder height"), free(cylinder),
			free_array(res), 1);
	if (parse_rgb(res[4], &colour) == 1)
		return (error("Invalid cylinder colour"), free(cylinder),
			free_array(res), 1);
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->colour = colour;
	if (add_to_list(&scene->obj_list, cylinder, CY, cylinder->colour) == 1)
		return (error("Failed adding cylinder to the list"), free(cylinder),
			free_array(res), 1);
	printf("CYLINDR\n");
	printf("cy cent %f %f %f\n", cylinder->cy_center.x, cylinder->cy_center.y,
		cylinder->cy_center.z);
	printf("norm %f %f %f\n", cylinder->normal.x, cylinder->normal.y,
		cylinder->normal.z);
	printf("diam %f\n", cylinder->diameter);
	printf("height %f", cylinder->height);
	printf("color %d\n\n", cylinder->colour);
	free_array(res);
	return (0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
// STEP 3: Main parsing functions for Cam Ambient Light
// Extracting basic data

// refractors below
//<0,2 255,255,255>
int	parse_ambient(char *line, t_scene *scene)
{
	char	**res;
	float	ratio;
	int		colour;

	if (scene->qt_ambiant > 1)
		return (error("Only 1 Ambient is allowed"), 1);
	if (count_elements(line) != 2)
		return (error("Wrong Ambient specs"), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), 1);
	ratio = 0.0f;
	colour = 0;
	if (parse_float(res[0], 0.0f, 1.0f, &ratio) == 1)
		return (error("Invalid Ambient ratio"), free_array(res), 1);
	if (parse_rgb(res[1], &colour) == 1)
		return (error("Invalid Ambient colour"), free_array(res), 1);
	scene->ambient.amb = ratio;
	scene->ambient.colour = colour;
	free_array(res);
	return (0);
}
int	parse_light(char *line, t_scene *scene)
{
	char	**res;
	float	bright;
	int		colour;

	if (scene->qt_light > 1)
		return (error("Only 1 light is allowed"), 1);
	if (count_elements(line) != 3) // or 2 for mandotary
		return (error("Invalid light specs"), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), 1);
	bright = 0.0f;
	colour = 0;
	if (parse_vector(res[0], &scene->light.pos, -100.0f, 100.0f) == 1)
		return (error("Invalid light position"), free_array(res), 1);
	if (parse_float(res[1], 0.0f, 1.0f, &bright) == 1)
		return (error("Invalid light brightness"), free_array(res), 1);
	if (parse_rgb(res[2], &colour) == 1) // this is for bonus
		return (error("Invalid light colour"), free_array(res), 1);
	scene->light.bright = bright;
	scene->light.color = colour; // this is for bonus
	free_array(res);
	return (0);
}
int	parse_cam(char *line, t_scene *scene)
{
	char	**res;
	float	fov;

	if (scene->qt_cam > 1)
		return (error("Only 1 camera is alowed"), 1);
	if (count_elements(line) != 3)
		return (error("Wrong specs for camera"), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), 1);
	if (parse_vector(res[0], &scene->cam.view_point, -100.0f, 100.0f) == 1)
		return (error("Invalid camera view point"), free_array(res), 1);
	if (parse_vector(res[1], &scene->cam.orient, 0.0f, 1.0f) == 1)
		return (error("Invalid camera orientation"), free_array(res), 1);
	fov = 0;
	if (parse_float(res[2], 0.0f, 180.0f, &fov) == 1)
		return (error("Invalid camera FOV"), free_array(res), 1);
	scene->cam.fov = fov;
	free_array(res);
	return (0);
}
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
// STEP 2: Read lines from input file with  gnl(need to change version)
// Trims spaces and newlines
// Passes trimmed line to dispatcher
// Based on identifier C L A sp pl cy to corresponding parsing function

// if ch == C -> pars_cam
// if ch == L -> pars_lignt
// if ch == A -> pars_ambient
// need to know that we have 1 of each, else, err
int	pars_cam_light(char *line, char ch, t_scene *scene)
{
	if (ch == 'C')
	{
		scene->qt_cam++;
		return (parse_cam(++line, scene));
	}
	else if (ch == 'A')
	{
		scene->qt_ambiant++;
		return (parse_ambient(++line, scene));
	}
	else if (ch == 'L')
	{
		scene->qt_light++;
		return (parse_light(++line, scene));
	}
	// we need a func to count CAL at the end of pars
	return (0);
}

int	dispatch(char *line, t_scene *scene)
{
	// while (*line == ' ') // what about tabs here ??
	// 	line++;
	if (*line == '\0' || *line == '\n')
		// what else is ok?  probably # (comments)
		return (0);
	else if (ft_strchr("CAL", *line))
		return (pars_cam_light(line, *line, scene));
	else if (ft_strncmp(line, "sp", 2) == 0)
	{
		line += 2;
		return (parse_sphere(line, scene));
	}
	else if (ft_strncmp(line, "pl", 2) == 0)
	{
		line += 2;
		return (parse_plane(line, scene));
	}
	else if (ft_strncmp(line, "cy", 2) == 0)
	{
		line += 2;
		return (parse_cylinder(line, scene));
	}
	else
		return (error("Unknown char detected in .rt"), 1);
}

int	pars_input_file(char *file, t_scene *scene)
{
	int		fd;
	int		check;
	char	*line;
	char	*trimmed;

	check = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("cannot open file for reading"), 1);
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \n");
		free(line);
		if (!trimmed)
		{
			close(fd);
			return (error(ERR_ALLOC), 1);
		}
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
	// another func to check amb/cam/light
	// should have qty == 1 of each.
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
// STEP 1: Checks ac and file extension

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
	scene->qt_ambiant = 0;
	scene->qt_cam = 0;
	scene->qt_light = 0;
	// scene->light = NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////

int	main(int ac, char **av)
{
	t_scene	scene;

	init_scene(&scene);
	if (confirm_input(ac, av) == 1)
	{
		kill_all(&scene);
		return (EXIT_FAILURE);
	}
	if (pars_input_file(av[1], &scene) == 1)
	{
		kill_all(&scene);
		return (EXIT_FAILURE);
	}
	print_vars(&scene);
	print_list(&scene);
	kill_all(&scene);
	return (0);
}

void	print_list(t_scene *scene)
{
	t_olist	*curr;
	int		i;

	curr = scene->obj_list;
	i = 0;
	while (curr)
	{
		printf("Objects num  %d in object list\n", i);
		printf("Object enunm num %d\n", curr->obj_type);
		curr = curr->next;
		i++;
	}
	printf("End printing object list\n");
}

void	print_vars(t_scene *scene)
{
	printf("TESTING PARSING\n");
	printf("---------------------------------------------------\n");
	printf("Ambient Parsing\n");
	printf("Ambient lighting ratio in the range [0.0,1.0]: ");
	printf("%f\n", scene->ambient.amb);
	printf("Ambient R, G, B colors in the range [0-255]: ");
	printf("%d\n", scene->ambient.colour);
	printf("---------------------------------------------------\n");
	printf("Camera Parsing\n");
	printf("x, y, z coordinates of the viewpoint: ");
	printf("%f ", scene->cam.view_point.x);
	printf("%f ", scene->cam.view_point.y);
	printf("%f \n", scene->cam.view_point.z);
	printf("3D norm orientation vector, in the range [-1,1] for x, y, z axis:");
	printf("%f ", scene->cam.orient.x);
	printf("%f ", scene->cam.orient.y);
	printf("%f\n", scene->cam.orient.z);
	printf("FOV: Horizontal field of view in degrees in the range [0,180]: ");
	printf("%f\n", scene->cam.fov);
	printf("---------------------------------------------------\n");
	printf("Light Parsing\n");
	printf("x, y, z coordinates of the light point: ");
	printf("%f ", scene->light.pos.x);
	printf("%f ", scene->light.pos.y);
	printf("%f \n", scene->light.pos.z);
	printf("the light brightness ratio in the range [0.0,1.0]: ");
	printf("%f \n", scene->light.bright);
	printf("(BONUS) R, G, B colors in the range [0-255]: ");
	printf("%d\n\n", scene->light.color);
}
