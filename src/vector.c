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

bool	is_equalf(float a, float b)
{
	if (fabsf(a - b) < EPSILON)
		return (true);
	return (false);
}

bool	is_point(t_vec3 v)
{
	return (v.w == 1);
}

t_vec3	vector_negate(t_vec3 v)
{
	return (new_vector(-v.x, -v.y, -v.z));
}

t_vec3	vector_add(t_vec3 a, t_vec3 b)
{
	if (is_point(a) && is_point(b))
		printf("Error: adding two points\n");
	if (is_point(a) || is_point(b))
		return(new_point(
			a.x + b.x,
			a.y + b.y,
			a.z + b.z
		));
	return(new_vector(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	));
}

t_vec3	vector_substract(t_vec3 a, t_vec3 b)
{
	if (!is_point(a) && is_point(b))
		printf("Error: substracting point from vector\n");
	if (is_point(a) != is_point(b))
		return(new_point(
			a.x - b.x,
			a.y - b.y,
			a.z - b.z
		));
	return(new_vector(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	));
}

t_vec3	vector_multiply(t_vec3 v, float scalar)
{
	if (is_point(v))
		printf("Error: multiplying a point\n");
	return (new_vector(
		v.x * scalar,
		v.y * scalar,
		v.z * scalar
	));
}

t_vec3	vector_divide(t_vec3 v, float scalar)
{
	if (is_point(v))
		printf("Error: dividing a point\n");
	//if (is_equalf(scalar, 0f))
	if (scalar == 0)
		printf("Error: dividing by zero\n");
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
		printf("Error: calculating magnitude of a point\n");
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
  a * b = |a||b|cos(angle)
*/
float	vector_dot(t_vec3 a, t_vec3 b)
{
	if (is_point(a) || is_point(b))
		printf("Error: calculating dot product of a point\n");
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vector_cross(t_vec3 a, t_vec3 b)
{
	if (is_point(a) || is_point(b))
		printf("Error: calculating cross product of a point\n");
	return (new_vector(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	));
}

float	degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180);
}
