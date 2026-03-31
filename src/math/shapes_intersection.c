#include "minirt.h"

static void hit_sp(t_ray ray, t_shape *sp, t_intersection *intersection);
static void hit_cy(t_ray ray, t_shape *cy, t_intersection *intersection);
static void	check_cy_cap(t_ray ray, t_ray cap_normal, float *hit, float radius);
static void hit_pl(t_ray ray, t_shape *pl, t_intersection *intersection);

t_intersection get_intersection(t_ray ray, t_shape *shape)
{
	t_intersection	intersection;

	intersection.count = 0;
	if (shape->obj_type == SP)
		hit_sp(ray, shape, &intersection);
	else if (shape->obj_type == CY)
		hit_cy(ray, shape, &intersection);
	else if (shape->obj_type == PL)
		hit_pl(ray, shape, &intersection);
	return (intersection);
}

static void hit_sp(t_ray ray, t_shape *sp, t_intersection *intersection)
{
	t_quad	quad;

	intersection->shape = sp;
	quad.vec_to_obj = vector_substract(ray.origin, sp->center);
	quad.a = vector_dot(ray.direction, ray.direction);
	quad.b = 2 * vector_dot(ray.direction, quad.vec_to_obj);
	quad.c = vector_dot(quad.vec_to_obj, quad.vec_to_obj)
		- sp->radius * sp->radius;
	solve_quadratic_equasion(quad, intersection);
}

static void hit_pl(t_ray ray, t_shape *pl, t_intersection *intersection)
{
	float	denominator;
	t_vec3	vec_to_obj;

	intersection->shape = pl;
	denominator = vector_dot(ray.direction, pl->normal.direction);
	if (fabsf(denominator) < EPSILON)
		return ;
	intersection->count = 1;
	vec_to_obj = vector_substract(ray.origin, pl->normal.origin);
	intersection->val[0] = vector_dot(vec_to_obj, pl->normal.direction)
		/ denominator;
}

static void hit_cy(t_ray ray, t_shape *cy, t_intersection *intersection)
{
	t_quad	quad;
	float	ray_proj;// projection of ray direction on cy axis
	float	obj_proj;// projection of origin_to_ray on cy axis
	t_vec3	ray_perp;
	t_vec3	obj_perp;
	t_ray	cap_normal;

	intersection->shape = cy;
	quad.vec_to_obj = vector_substract(ray.origin, cy->normal.origin);
	ray_proj = vector_dot(ray.direction, cy->normal.direction);
	obj_proj = vector_dot(quad.vec_to_obj, cy->normal.direction);

	ray_perp = vector_substract(ray.direction,
		vector_multiply(cy->normal.direction, ray_proj));
	obj_perp = vector_substract(quad.vec_to_obj,
		vector_multiply(cy->normal.direction, obj_proj));

	quad.a = vector_dot(ray_perp, ray_perp);
	quad.b = 2 * (vector_dot(ray_perp, obj_perp));
	quad.c = vector_dot(obj_perp, obj_perp) - cy->radius * cy->radius;
	solve_quadratic_equasion(quad, intersection);
	if (intersection->count == 0)
		return ;
	//Check side hits to cylinder heigth
	if (fabsf(ray_proj * intersection->val[0] + obj_proj) > cy->half_height)
		intersection->val[0] = -1;
	if (fabsf(ray_proj * intersection->val[1] + obj_proj) > cy->half_height)
		intersection->val[1] = -1;
	//Check cap hits
	if (fabsf(ray_proj) < EPSILON)
		return ;
	intersection->count = 4;
	//top cap
	cap_normal.origin = vector_add(cy->normal.origin, vector_multiply(
		cy->normal.direction, cy->half_height));
	cap_normal.direction = cy->normal.direction;
	check_cy_cap(ray, cap_normal, &intersection->val[2], cy->radius);

	//bottom cap
	cap_normal.origin = vector_substract(cy->normal.origin, vector_multiply(
		cy->normal.direction, cy->half_height));
	cap_normal.direction = vector_negate(cy->normal.direction);
	check_cy_cap(ray, cap_normal, &intersection->val[3], cy->radius);
}

static void	check_cy_cap(t_ray ray, t_ray cap_normal, float *hit, float radius)
{
	t_vec3	vec_to_obj;
	float	ray_proj;
	t_vec3	hit_point;

	vec_to_obj = vector_substract(cap_normal.origin, ray.origin);
	ray_proj = vector_dot(ray.direction, cap_normal.direction);
	*hit = vector_dot(vec_to_obj, cap_normal.direction) / ray_proj;
	hit_point = get_ray_point(ray, *hit);
	if (vector_magnitude(vector_substract(hit_point, cap_normal.origin)) > radius)
		*hit = -1;
}
