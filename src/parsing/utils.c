#include "minirt.h"

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

void	error(char *msg, char *line)
{
	ft_putendl_fd(ERR_MSG, 2);
	ft_putendl_fd(msg, 2);
	if (line != NULL)
		ft_printf("Problem in line: %s\n", line);
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
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 0. fix

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
			if (ft_isdigit(line[i + 1]) == 0)
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
		return (error(ERR_ALLOC, NULL), 1);
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
		return (error(ERR_ALLOC, NULL), 1);
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
