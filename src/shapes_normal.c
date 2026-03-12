#include "minirt.h"

static t_vec3	normal_at_sp(t_vec3 point, t_shape *sp);

t_vec3	get_normal(t_shape *shape, t_vec3 point)
{
	if (shape->obj_type == SP)
		return (normal_at_sp(point, shape));
	if (shape->obj_type == PL)
		return (shape->normal.direction);
	else
		return (point);
}

static t_vec3	normal_at_sp(t_vec3 point, t_shape *sp)
{
	t_vec3	normal;

	normal = vector_substract(point, sp->center);
	normal = vector_normalize(normal);
	return (normal);
}
