#include "minirt.h"

t_intersection	hit_sp(t_ray ray, t_sp *sp)
{
	float			a;
	float			b;
	float			c;
	t_vec3			vector_to_sphere;
	float			discriminant;
	t_intersection	intersection;

	//sp_set_matrix(sp, new_scaling_matrix(2, 2, 2));
	//ray = ray_transform(ray, sp->matrix);

	vector_to_sphere = vector_substract(ray.origin, sp->sp_center);
	a = vector_dot(ray.direction, ray.direction);
	b = 2 * vector_dot(ray.direction, vector_to_sphere);
	c = vector_dot(vector_to_sphere, vector_to_sphere) - sp->diameter
		* sp->diameter / 4;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		intersection.count = 0;
	else//Find intersection:
	{
		intersection.count = 2;
		intersection.val[0] = (-b - sqrtf(discriminant)) / (2 * a);
		intersection.val[1] = (-b + sqrtf(discriminant)) / (2 * a);
	}
	return (intersection);
}

t_intersection	hit_cy(t_ray ray, t_cy *cy)
{
	t_intersection	intersection;

	(void)ray;
	(void)cy;
	intersection.count = 0;
	return (intersection);
}

t_intersection	hit_pl(t_ray ray, t_pl *pl)
{
	float	denominator;
	float	multiplier;
	t_intersection	intersection;

	denominator = vector_dot(ray.direction, pl->normal.direction);
	if (fabsf(denominator) < EPSILON)//cam and palne (almost or fully) parallel
		intersection.count = 0;
	else//Find intersection:
	{
		intersection.count = 1;
		multiplier = -vector_dot(pl->normal.direction, vector_substract(ray.origin,
			pl->normal.origin)) / denominator;
		//intersection.val[0] = vector_multiply(ray.direction, multiplier);
	}
	return (intersection);
}

void	sp_set_matrix(t_sp *sp, t_matrix m)
{
	free_matrix(sp->matrix);
	sp->matrix = m;
}
