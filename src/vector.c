#include "minirt.h"

t_vec3	new_vector(float x, float y, float z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = 0;
	return (res);
}

t_vec3	new_point(float x, float y, float z)
{
	t_vec3	res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = 1;
	return (res);
}

bool	is_point(t_vec3 v)
{
	return (v.w == 1);
}

bool	is_equalf(float f1, float f2)
{
	if (fabsf(f1 - f2) < EPSILON)
		return (true);
	return (false);
}

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
	if (is_equalf(scalar, 0))
	//if (scalar == 0)
		ft_putendl_fd("Error: dividing by zero", STDERR_FILENO);
	return (new_vector(
		v.x / scalar,
		v.y / scalar,
		v.z / scalar
	));
}

//Do we need to include v.w here? It's 0 for vectors...
/* If magnitude equals 1 - it is a unit vector. */
float	vector_magnitude(t_vec3 v)
{
	if (is_point(v))
		ft_putendl_fd("Error: calculating magnitude of a point", STDERR_FILENO);
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vector_normalize(t_vec3 v)
{
	float	magnitude;

	magnitude = vector_magnitude(v);
	if (is_equalf(magnitude, 1))
		return (v);
	return (vector_divide(v, magnitude));
}

/* The smaller the dot product - the larger the angle between the vectors.

 For unit vectors: 
  Dot product is cosine of the angle between vectors.
  1 - vectors are identical;
 -1 - vectors are opposite.
 
 For other vectors:
  v1 * v2 = |v1||v2|cos(angle)
*/
float	vector_dot(t_vec3 v1, t_vec3 v2)
{
	if (is_point(v1) || is_point(v2))
		ft_putendl_fd("Error: calculating dot product of a point", STDERR_FILENO);
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vector_cross(t_vec3 v1, t_vec3 v2)
{
	if (is_point(v1) || is_point(v2))
		ft_putendl_fd("Error: calculating cross product of a point", STDERR_FILENO);
	return (new_vector(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	));
}

float	degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180);
}
