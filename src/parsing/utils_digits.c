#include "minirt.h"

static int	ft_rgbtoint(int transp, int red, int green, int blue);

int	parse_int(char *str, int min, int max, int *res)
{
	int	temp;
	int	overflow;

	overflow = 0;
	temp = 0;
	if (!str || is_valid_int(str))
		return (1);
	temp = ft_atoi_and_overflow(str, &overflow);
	if (temp < min || temp > max || overflow == 1)
		return (1);
	*res = temp;
	return (0);
}

int	parse_float(char *str, float min, float max, float *res)
{
	if (!str || is_valid_float(str))
		return (1);
	if (ft_atof(str, res))
		return (1);
	if (*res < min || *res > max)
		return (1);
	return (0);
}

int	parse_vector(char *str, t_vec3 *vector, float min, float max)
{
	char	**res;

	if (!str || is_valid_comas(str) == 1)
		return (1);
	res = ft_split(str, ',');
	if (!res)
		return (error_return(ERR_ALLOC, NULL));
	if (!res[0] || !res[1] || !res[2] || res[3])
		return (free_array(res), 1);
	if (parse_float(res[0], min, max, &vector->x) || parse_float(res[1], min,
			max, &vector->y) || parse_float(res[2], min, max, &vector->z))
		return (free_array(res), 1);
	free_array(res);
	if (vector_is_zero(*vector))
		return (error_return(ERR_VEC_ZERO, NULL));
	return (0);
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
		return (error_return(ERR_ALLOC, NULL));
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_array(rgb), 1);
	r = 0;
	g = 0;
	b = 0;
	if (parse_int(rgb[0], 0, 255, &r) || parse_int(rgb[1], 0, 255, &g)
		|| parse_int(rgb[2], 0, 255, &b))
		return (free_array(rgb), 1);
	*color = ft_rgbtoint(255, r, g, b);
	free_array(rgb);
	return (0);
}

static int	ft_rgbtoint(int transp, int red, int green, int blue)
{
	return (transp << 24 | red << 16 | green << 8 | blue);
}
