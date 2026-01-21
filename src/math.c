#include "minirt.h"

bool	hit_sp(t_vec3 cam, t_sp *sp)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;

	a = vector_dot(cam, cam);
	b = 2 * vector_dot(sp->sp_center, cam);
	c = vector_dot(sp->sp_center, sp->sp_center) - sp->diameter * sp->diameter / 4;
	discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

bool	hit_cy(t_vec3 cam, t_cy *cy)
{
	return (0);
}

bool	hit_pl(t_vec3 cam, t_pl *pl)
{
	float	denominator;

	denominator = vector_dot(cam, pl->normal);
	if (abs(denominator) < EPSILON)
		return (false);
	//Find intersection:
	//difference = pl->center - 0.0.0 <- cam center
	//t = vector_dot(difference, pl->normal) / denominator;
	return (true);
}
