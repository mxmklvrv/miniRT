#include "minirt.h"

t_sphere	*sphere_new(t_vec3 *center, float radius)
{
	t_sphere *sp;
	sp = malloc(sizeof(t_sphere));
	if (!sp)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	sp->center = center;
	sp->radius = radius;
	return (sp);
}