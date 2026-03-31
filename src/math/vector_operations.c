#include "minirt.h"

t_vec3	vector_negate(t_vec3 v)
{
	return (new_vector(-v.x, -v.y, -v.z));
}

t_vec3	vector_add(t_vec3 v1, t_vec3 v2)
{
	if (is_point(v1) && is_point(v2))
		ft_putendl_fd("Error: adding two points", STDERR_FILENO);
	if (is_point(v1) || is_point(v2))
		return(new_point(
			v1.x + v2.x,
			v1.y + v2.y,
			v1.z + v2.z
		));
	return(new_vector(
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	));
}

t_vec3	vector_substract(t_vec3 v1, t_vec3 v2)
{
	if (!is_point(v1) && is_point(v2))
		ft_putendl_fd("Error: substracting point from vector", STDERR_FILENO);
	if (is_point(v1) != is_point(v2))
		return(new_point(
			v1.x - v2.x,
			v1.y - v2.y,
			v1.z - v2.z
		));
	return(new_vector(
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	));
}

t_vec3	vector_multiply(t_vec3 v, float scalar)
{
	if (is_point(v))
		ft_putendl_fd("Error: multiplying a point", STDERR_FILENO);
	return (new_vector(
		v.x * scalar,
		v.y * scalar,
		v.z * scalar
	));
}

t_vec3	vector_divide(t_vec3 v, float scalar)
{
	if (is_point(v))
		ft_putendl_fd("Error: dividing a point", STDERR_FILENO);
	if (scalar == 0)
	{
		ft_putendl_fd("Error: dividing by zero", STDERR_FILENO);
		return (v);
	}
	return (new_vector(
		v.x / scalar,
		v.y / scalar,
		v.z / scalar
	));
}
