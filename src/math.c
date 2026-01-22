#include "minirt.h"

int	hit_sp(t_vec3 cam, t_sp *sp)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_vec3	intersection;

	a = vector_dot(cam, cam);
	b = 2 * vector_dot(sp->sp_center, cam);
	c = vector_dot(sp->sp_center, sp->sp_center) - sp->diameter * sp->diameter / 4;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	//Find intersection:
	intersection = cam;//TODO: find intersection with sphere
	return (vector_length(intersection));
}

int	hit_cy(t_vec3 cam, t_cy *cy)
{
	return (-1);
}

int	hit_pl(t_vec3 cam, t_pl *pl)
{
	float	denominator;
	float	multiplier;
	t_vec3	intersection;

	denominator = vector_dot(cam, pl->normal);
	if (abs(denominator) < EPSILON)
		return (-1);
	//Find intersection:
	multiplier = vector_dot(pl->pl_point, pl->normal) / vector_dot(cam, pl->normal);
	intersection = vector_multiply(cam, multiplier);
	return (vector_length(intersection));
}
