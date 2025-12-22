#ifndef SPHERE_H
# define SPHERE_H

#include "vector.h"
typedef struct s_sphere
{
	t_vec3	*center;
	float	radius;
}			t_sphere;

t_sphere	*sphere_new(t_vec3 *center, float radius);

#endif