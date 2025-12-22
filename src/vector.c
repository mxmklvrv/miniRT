#include "minirt.h"

/**
 * Vector is a list of nums that desribes direction and position in space.
 * Smth like an arrow
 * where i starts -> origin
 * where it points -> direction
 */

/**
 * Allocates memory for a vector.
 * Sets its values and returns a pointer to it.
 */
t_vec3	*vec_new(float x, float y, float z)
{
	t_vec3	*vec;

	vec = malloc(sizeof(t_vec3));
	if (!vec)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}
/**
 * To find direction from vec2 to vec1
 */
t_vec3	*vec_substr(t_vec3 *vec1, t_vec3 *vec2)
{
	t_vec3	*res;

	res = vec_new(vec1->x - vec2->x, vec1->y - vec2->y, vec1->z - vec2->z);
	return (res);
}

/**
 * To find vector length
 */
float	vec_len(t_vec3 *vec)
{
	float	res;

	res = sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
	return (res);
}

/**
 * Modifies a vector so its lenght == 1, dir is the same.
 * Made for ray tracing math
 */
void	vec_norm(t_vec3 *vec)
{
	float	len;

	len = vec_len(vec);
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
}

/**
 * to measure how aligned two directions are.
 */
float	vec_dot(t_vec3 *vec1, t_vec3 *vec2)
{
	float	res;

	res = ((vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z));
	return (res);
}
