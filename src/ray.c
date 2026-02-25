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

t_ray	ray_transform(t_ray r, t_matrix m)
{
	t_ray		res;
	t_matrix	inverse;

	inverse = new_inverse_matrix(m);
	res.origin = matrix_multiply_by_vector(inverse, r.origin);
	res.direction = matrix_multiply_by_vector(inverse, r.direction);
	free_matrix(inverse);
	return (res);
}
