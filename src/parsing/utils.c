#include "minirt.h"

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
