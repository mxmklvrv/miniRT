#include "minirt.h"

bool	is_equalf(float f1, float f2)
{
	if (fabsf(f1 - f2) < EPSILON)
		return (true);
	return (false);
}

 /* Converts degrees to radians.
 * @param	float	degrees	degrees of angle;
 * @returns	float	angle in radians.
 */
float	degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180);
}

void	solve_quadratic_equasion(t_quad quad, t_intersection *intersection)
{
	float	sqrt_discriminant;

	quad.discriminant = quad.b * quad.b - 4.0f * quad.a * quad.c;
	if (quad.discriminant < 0.0f || fabsf(quad.a) * 2.0f < EPSILON)
		return ;
	sqrt_discriminant = sqrtf(quad.discriminant);
	intersection->count = 2;
	intersection->val[0] = (-quad.b - sqrt_discriminant) / (2.0f * quad.a);
	intersection->val[1] = (-quad.b + sqrt_discriminant) / (2.0f * quad.a);
}
