#include "minirt.h"

t_ray	new_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	if (!is_point(origin))
		ft_putendl_fd("Error: creating ray: origin is not a point", STDERR_FILENO);
	if (is_point(direction))
		ft_putendl_fd("Error: creating ray: direction is not a vector", STDERR_FILENO);
	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_vec3	get_position(t_ray ray, float distance)
{
	return (vector_add(ray.origin, vector_multiply(ray.direction, distance)));
}

