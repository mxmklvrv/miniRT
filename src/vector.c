#include "minirt.h"

bool	vector_is_zero(t_vec3 vec)
{
	return (vec.x == 0 && vec.y == 0 && vec.z == 0);
}

void	vector_to_zero(t_vec3 *vec)
{
	vec->x = 0;
	vec->y = 0;
	vec->z = 0;
}

t_vec3	vector_add(t_vec3 from, t_vec3 to)
{
	t_vec3	res;

	res.x = to.x - from.x;
	res.y = to.y - from.y;
	res.z = to.z - from.z;
	return (res);
}