#include "minirt.h"

static void	get_whole_part(const char *line, int *i, float *temp,
				int *overflow);
static void	get_fraction_part(const char *line, int *i, float *temp);

int	ft_atoi_and_overflow(const char *nptr, int *overflow)
{
	int		i;
	long	num;
	long	neg;

	i = 0;
	num = 0;
	neg = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		if ((num > INT_MAX && neg == 1) || (num > (long)INT_MAX + 1 && neg ==
				-1))
			*overflow = 1;
		i++;
	}
	return ((int)num * neg);
}

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
	if (!overflow)
	{
		get_fraction_part(line, &i, &temp);
		*res = temp * sign;
	}
	return (overflow);
}

static void	get_whole_part(const char *line, int *i, float *temp, int *overflow)
{
	while (ft_isdigit(line[*i]))
	{
		*temp = *temp * 10 + (line[*i] - '0');
		if (*temp > FLT_MAX)
			*overflow = 1;
		(*i)++;
	}
}

static void	get_fraction_part(const char *line, int *i, float *temp)
{
	float	fraction;

	fraction = 0.1f;
	if (line[*i] == '.')
		(*i)++;
	while (ft_isdigit(line[*i]))
	{
		*temp += (line[*i] - '0') * fraction;
		fraction *= 0.1f;
		(*i)++;
	}
}
