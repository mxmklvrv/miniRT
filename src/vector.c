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

t_vec3	vector_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vec3	vector_remove(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vec3	vector_multiply(t_vec3 v, float multiplier)
{
	v.x *= multiplier;
	v.y *= multiplier;
	v.z *= multiplier;
	return (v);
}

float	vector_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	vector_length(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}
