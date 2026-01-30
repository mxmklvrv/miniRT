#include "minirt.h"

int	hit_sp(t_ray ray, t_sp *sp)
{
	float	a;
	float	b;
	float	c;
	t_vec3	vector_to_sphere;
	float	discriminant;
	t_vec3	intersection;

	vector_to_sphere = vector_remove(ray.origin, sp->sp_center);
	a = vector_dot(ray.direction, ray.direction);
	b = 2 * vector_dot(vector_to_sphere, ray.direction);
	c = vector_dot(vector_to_sphere, vector_to_sphere) - sp->diameter
		* sp->diameter / 4;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	//Find intersection:
	intersection = ray.direction;//TODO: find intersection with sphere
	//vector_length(intersection)
	return (1);
}

int	hit_cy(t_ray ray, t_cy *cy)
{
	(void)ray;
	(void)cy;
	return (-1);
}

int	hit_pl(t_ray ray, t_pl *pl)
{
	float	denominator;
	float	multiplier;
	t_vec3	intersection;
	static int	message_pl = 0;
	float		distance;

	denominator = vector_dot(ray.direction, pl->normal.direction);
	if (fabsf(denominator) < EPSILON)//cam and palne (almost or fully) parallel
	{
		if (message_pl == 0)
		{
			message_pl = 1;
			printf("Plane is parallel!\n");
		}
		return (-1);
	}
	//Find intersection:
	multiplier = -vector_dot(pl->normal.direction, vector_remove(ray.origin,
		pl->normal.origin)) / denominator;
	if (multiplier < 0)//intersection is behind camera
	{
		if (message_pl == 0)
		{
			message_pl = 1;
			printf("Intersection behind camera!\n");
		}
		return (-1);
	}
	intersection = vector_multiply(ray.direction, multiplier);
	distance = vector_length(intersection);
	if (message_pl == 0)
	{
		message_pl++;
		printf("denominator = %f, multiplier = %f\n", denominator, multiplier);
		printf("Found intersection, distance = %f\n", distance);
	}
	return (distance);
}

float	degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180);
}
