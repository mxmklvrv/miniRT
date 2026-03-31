#include "minirt.h"

static void hit_sp(t_ray ray, t_shape *sp, t_intersection *intersection);
static void hit_cy(t_ray ray, t_shape *cy, t_intersection *intersection);
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

//static void hit_cy(t_ray ray, t_shape *cy, t_intersection *intersection)
//{
//	t_quad	quad;
//	float	ray_proj;
//	float	obj_proj;
//	t_vec3	ray_perp;
//	t_vec3	obj_perp;
//	t_vec3	disc_center;
//	t_vec3	hit_point;
//	float	heigth_proj;

//	intersection->shape = cy;
//	quad.vec_to_obj = vector_substract(ray.origin, cy->normal.origin);
//	ray_proj = vector_dot(ray.direction, cy->normal.direction);
//	obj_proj = vector_dot(quad.vec_to_obj, cy->normal.direction);

//	ray_perp = vector_substract(ray.direction,
//		vector_multiply(cy->normal.direction, ray_proj));
//	obj_perp = vector_substract(quad.vec_to_obj,
//		vector_multiply(cy->normal.direction, obj_proj));

//	quad.a = vector_dot(ray_perp, ray_perp);
//	quad.b = 2 * (vector_dot(ray_perp, obj_perp));
//	quad.c = vector_dot(obj_perp, obj_perp) - cy->radius * cy->radius;
//	solve_quadratic_equasion(quad, intersection);
//	if (intersection->count == 0)
//		return ;
//	//Check side hits to cylinder heigth
//	if (intersection->val[0] < EPSILON || fabsf(ray_proj * intersection->val[0]
//		+ obj_proj) > cy->half_height)
//		intersection->val[0] = -1;
//	if (intersection->val[0] < EPSILON || fabsf(ray_proj * intersection->val[1]
//		+ obj_proj) > cy->half_height)
//		intersection->val[1] = -1;
//	if (fabsf(ray_proj) < EPSILON)
//		return ;
//	intersection->count = 4;
//	//top cap
//	disc_center = vector_add(cy->normal.origin, vector_multiply(
//		cy->normal.direction, cy->half_height));
//	quad.vec_to_obj = vector_substract(ray.origin, disc_center);
//	obj_proj = vector_dot(quad.vec_to_obj, cy->normal.direction);
//	intersection->val[2] = obj_proj / ray_proj;
//	hit_point = get_ray_point(ray, intersection->val[2]);
//	if (vector_magnitude(vector_substract(hit_point, disc_center)) > cy->radius)
//		intersection->val[2] = -1;
//	//bottom cap
//	disc_center = vector_substract(cy->normal.origin, vector_multiply(
//		cy->normal.direction, cy->half_height));
//	quad.vec_to_obj = vector_substract(ray.origin, disc_center);
//	obj_proj = vector_dot(quad.vec_to_obj, cy->normal.direction);
//	intersection->val[3] = obj_proj / ray_proj;
//	hit_point = get_ray_point(ray, intersection->val[3]);
//	if (vector_magnitude(vector_substract(hit_point, disc_center)) > cy->radius)
//		intersection->val[2] = -1;
//}


//static void set_cy_quad(t_ray ray, t_shape *cy, t_cy_geom *data, t_quad *side);
//static void append_cy_side_hit(t_shape *cy,t_cy_geom *data, t_intersection *it, float t);
//static void add_cy_side_hits(t_shape *cy, t_quad *side, t_cy_geom *data, t_intersection *it);
//static void add_cy_caps(t_ray ray, t_shape *cy, t_intersection *it);
//static void add_cap_hit(t_ray ray, float t, t_disk disk, t_intersection *it);

//typedef struct s_quad
//{
//	t_vec3 ray_perp; // ray direction component perpendicular to cy axis
//	t_vec3 oc_perp; // origin_to_ray component perpendicular to cy axis
//	float	a;
//	float	b;
//	float	c;
//	float	discriminant;
//} t_quad;

//typedef struct s_disk
//{
//	t_vec3 center;
//	float radius;
//} t_disk;

static void hit_cy(t_ray ray, t_shape *cy, t_intersection *intersection)
{
	t_quad side;
	t_vec3 oc_perp;
	t_vec3 ray_perp;
	//t_cy_geom;
	//t_vec3 origin_to_ray;// vector from cy center to ray origin
	float ray_axis;// projection of ray direction on cy axis
	float oc_axis;// projection of origin_to_ray on cy axis

	//init_cy_data(t_ray ray, t_shape *cy, t_cy_geom *data);
	side.vec_to_obj = vector_substract(ray.origin, cy->normal.origin);
	ray_axis = vector_dot(ray.direction, cy->normal.direction);
	oc_axis = vector_dot(side.vec_to_obj, cy->normal.direction);

	//set_cy_quad(ray, cy, &data, &side);
	ray_perp = vector_substract(ray.direction,
		vector_multiply(cy->normal.direction, ray_axis));
	oc_perp = vector_substract(side.vec_to_obj,
		vector_multiply(cy->normal.direction, oc_axis));
	side.a = vector_dot(ray_perp, ray_perp);
	side.b = 2.0f * vector_dot(ray_perp, oc_perp);
	side.c = vector_dot(oc_perp, oc_perp) - cy->radius * cy->radius;
	side.discriminant = side.b * side.b - 4.0f * side.a * side.c;

	//add_cy_side_hits(cy, &side, &data, intersection);
	float t0;
	float t1;
	float sqrt_discrimimnant;
	if (fabsf(side.a) < EPSILON || side.discriminant < 0.0f)
		return;
	sqrt_discrimimnant = sqrtf(side.discriminant);
	t0 = (-side.b - sqrt_discrimimnant) / (2.0f * side.a);
	t1 = (-side.b + sqrt_discrimimnant) / (2.0f * side.a);

	//append_cy_side_hit(cy, data, it, t0);
	float h;
	h = oc_axis + t0 * ray_axis;
	if (t0 > EPSILON && h >= -cy->half_height && h <= cy->half_height && intersection->count < 4)
		intersection->val[intersection->count++] = t0;
	//append_cy_side_hit(cy, data, it, t1);
	h = oc_axis + t1 * ray_axis;
	if (t1 > EPSILON && h >= -cy->half_height && h <= cy->half_height && intersection->count < 4)
		intersection->val[intersection->count++] = t1;

	//add_cy_caps(ray, cy, intersection);
	float denom;
	float t;
	t_vec3 center;
	float radius;
	denom = vector_dot(ray.direction, cy->normal.direction);
	if (fabsf(denom) <= EPSILON)
		return;
	radius = cy->radius;
	// bottom cap
	center = vector_add(cy->normal.origin,
		vector_multiply(cy->normal.direction, -cy->half_height));
	t = vector_dot(vector_substract(center, ray.origin),
		cy->normal.direction) / denom;

	//add_cap_hit(ray, t, disk, it);
	t_vec3 hit_point;
	t_vec3 to_center;
	if (t < EPSILON || intersection->count >= 4)
		return;
	hit_point = get_ray_point(ray, t);
	to_center = vector_substract(hit_point, center);
	if (vector_dot(to_center, to_center) <= radius * radius)
		intersection->val[intersection->count++] = t;
	// top cap
	center = vector_add(cy->normal.origin,
		vector_multiply(cy->normal.direction, cy->half_height));
	t = vector_dot(vector_substract(center, ray.origin),
		cy->normal.direction) / denom;

	//add_cap_hit(ray, t, disk, it);
	if (t < EPSILON || intersection->count >= 4)
		return;
	hit_point = get_ray_point(ray, t);
	to_center = vector_substract(hit_point, center);

	if (vector_dot(to_center, to_center) <= radius * radius)
		intersection->val[intersection->count++] = t;
}

/* 
 * Initializes geometric data for the cylinder side calculation.
 * Computes projections along the cylinder axis needed for quadratic formula.
 */
//static void init_cy_data(t_ray ray, t_shape *cy, t_cy_geom *data)
//{
//	data->origin_to_ray = vector_substract(ray.origin, cy->normal.origin);
//	data->ray_axis = vector_dot(ray.direction, cy->normal.direction);
//	data->oc_axis = vector_dot(data->origin_to_ray, cy->normal.direction);
//}

// Build quadratic equation for intersection with infinite cylinder side
//static void set_cy_quad(t_ray ray, t_shape *cy, t_cy_geom *data, t_quad *side)
//{
//	side->ray_perp = vector_substract(ray.direction,
//		vector_multiply(cy->normal.direction, data->ray_axis));

//	side->oc_perp = vector_substract(data->origin_to_ray,
//		vector_multiply(cy->normal.direction, data->oc_axis));

//	side->a = vector_dot(side->ray_perp, side->ray_perp);
//	side->b = 2.0f * vector_dot(side->ray_perp, side->oc_perp);
//	side->c = vector_dot(side->oc_perp, side->oc_perp) - cy->radius * cy->radius;

//	side->discriminant = side->b * side->b - 4.0f * side->a * side->c;
//}

// Check if intersection lies within finite cylinder height
//static void append_cy_side_hit(t_shape *cy,t_cy_geom *data, t_intersection *it, float t)
//{
//	float h;

//	h = data->oc_axis + t * data->ray_axis;
//	if (t > EPSILON && h >= -cy->half_height && h <= cy->half_height && it->count < 4)
//		it->val[it->count++] = t;
//}

//// Solve quadratic and test valid intersections with cylinder side
//static void add_cy_side_hits(t_shape *cy, t_quad *side, t_cy_geom *data, t_intersection *it)
//{
//	float t0;
//	float t1;
//	float sqrt_discrimimnant;

//	if (fabsf(side->a) < EPSILON || side->discriminant < 0.0f)
//		return;

//	sqrt_discrimimnant = sqrtf(side->discriminant);
//	t0 = (-side->b - sqrt_discrimimnant) / (2.0f * side->a);
//	t1 = (-side->b + sqrt_discrimimnant) / (2.0f * side->a);

//	append_cy_side_hit(cy, data, it, t0);
//	append_cy_side_hit(cy, data, it, t1);
//}

//static void add_cy_caps(t_ray ray, t_shape *cy, t_intersection *it)
//{
//	float denom;
//	float t;
//	t_disk disk;

//	denom = vector_dot(ray.direction, cy->normal.direction);
//	if (fabsf(denom) <= EPSILON)
//		return;
//	disk.radius = cy->radius;
//	// bottom cap
//	disk.center = vector_add(cy->normal.origin,
//			vector_multiply(cy->normal.direction, -cy->half_height));
//	t = vector_dot(vector_substract(disk.center, ray.origin),
//			cy->normal.direction) / denom;
//	add_cap_hit(ray, t, disk, it);

//	// top cap
//	disk.center = vector_add(cy->normal.origin,
//			vector_multiply(cy->normal.direction, cy->half_height));
//	t = vector_dot(vector_substract(disk.center, ray.origin),
//			cy->normal.direction) / denom;
//	add_cap_hit(ray, t, disk, it);
//}

//static void add_cap_hit(t_ray ray, float t, t_disk disk, t_intersection *it)
//{
//	t_vec3 hit_point;
//	t_vec3 to_center;

//	if (t < EPSILON || it->count >= 4)
//		return;
//	hit_point = get_ray_point(ray, t);
//	to_center = vector_substract(hit_point, disk.center);

//	if (vector_dot(to_center, to_center) <= disk.radius * disk.radius)
//		it->val[it->count++] = t;
//}
