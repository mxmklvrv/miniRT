#include "minirt.h"

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

t_vec3	vector_reflect(t_vec3 v, t_vec3 normal)
{
	t_vec3	reflection;

	reflection = vector_multiply(normal, vector_dot(v, normal) * 2);
	reflection = vector_substract(v, reflection);
	return (reflection);
}
