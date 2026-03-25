#include "minirt.h"

static void hit_sp(t_ray ray, t_shape *sp, t_intersection *intersection);
static void hit_cy(t_ray ray, t_shape *cy, t_intersection *intersection);
static void hit_pl(t_ray ray, t_shape *pl, t_intersection *intersection);

typedef struct s_cy_geom
{
	t_vec3 origin_to_ray; // vector from cy center to ray origin
	float ray_axis; // projection of ray direction on cy axis
	float oc_axis; // projection of origin_to_ray on cy axis
} t_cy_geom;

typedef struct s_quad
{
	t_vec3 ray_perp; // ray direction component perpendicular to cy axis
	t_vec3 oc_perp; // origin_to_ray component perpendicular to cy axis
	float	a;
	float	b;
	float	c;
	float	discriminant;
} t_quad;

typedef struct s_disk
{
	t_vec3 center;
	float radius;
} t_disk;

static void init_cy_data(t_ray ray, t_shape *cy, t_cy_geom *data);
static void set_cy_quad(t_ray ray, t_shape *cy, t_cy_geom *data, t_quad *side);
static void append_cy_side_hit(t_shape *cy,t_cy_geom *data, t_intersection *it, float t);
static void add_cy_side_hits(t_shape *cy, t_quad *side, t_cy_geom *data, t_intersection *it);
static void add_cy_caps(t_ray ray, t_shape *cy, t_intersection *it);
static void add_cap_hit(t_ray ray, float t, t_disk disk, t_intersection *it);





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
	t_vec3			vector_to_sphere;
	t_quad			quad;
	float			sqrt_discriminant;

	intersection->shape = sp;
	vector_to_sphere = vector_substract(ray.origin, sp->center);
	quad.a = vector_dot(ray.direction, ray.direction);
	quad.b = 2 * vector_dot(ray.direction, vector_to_sphere);
	quad.c = vector_dot(vector_to_sphere, vector_to_sphere) - sp->diameter * sp->diameter / 4.0f;
	quad.discriminant = quad.b * quad.b - 4.0f * quad.a * quad.c;
	if (quad.discriminant < 0.0f || fabsf(quad.a) < EPSILON)
		return ;
	else // Find intersection:
	{
		sqrt_discriminant = sqrtf(quad.discriminant);
		intersection->count = 2;
		intersection->val[0] = (-quad.b - sqrt_discriminant) / (2.0f * quad.a);
		intersection->val[1] = (-quad.b + sqrt_discriminant) / (2.0f * quad.a);
	}
}

static void hit_pl(t_ray ray, t_shape *pl, t_intersection *intersection)
{
	float			denominator;

	intersection->shape = pl;
	denominator = vector_dot(ray.direction, pl->normal.direction);
	if (fabsf(denominator) < EPSILON) // cam and plane (almost or fully) parallel
		return ;
	else // Find intersection:
	{
		intersection->count = 1;
		intersection->val[0] = vector_dot(vector_substract(pl->normal.origin, ray.origin), pl->normal.direction) / denominator;
	}
}






static void add_cap_hit(t_ray ray, float t, t_disk disk, t_intersection *it)
{
	t_vec3 hit_point;
	t_vec3 to_center;

	if (t < EPSILON || it->count >= 4)
		return;
	hit_point = get_ray_point(ray, t);
	to_center = vector_substract(hit_point, disk.center);

	if (vector_dot(to_center, to_center) <= disk.radius * disk.radius)
		it->val[it->count++] = t;
}

/* 
 * Initializes geometric data for the cylinder side calculation.
 * Computes projections along the cylinder axis needed for quadratic formula.
 */
static void init_cy_data(t_ray ray, t_shape *cy, t_cy_geom *data)
{
	data->origin_to_ray = vector_substract(ray.origin, cy->normal.origin);
	data->ray_axis = vector_dot(ray.direction, cy->axis);
	data->oc_axis = vector_dot(data->origin_to_ray, cy->axis);
}

// Build quadratic equation for intersection with infinite cylinder side
static void set_cy_quad(t_ray ray, t_shape *cy, t_cy_geom *data, t_quad *side)
{
	side->ray_perp = vector_substract(ray.direction,
									  vector_multiply(cy->axis, data->ray_axis));

	side->oc_perp = vector_substract(data->origin_to_ray,
									 vector_multiply(cy->axis, data->oc_axis));

	//side->a = vector_dot(side->ray_perp, side->ray_perp);
	//side->b = 2.0f * vector_dot(side->ray_perp, side->oc_perp);
	//side->c = vector_dot(side->oc_perp, side->oc_perp) - cy->radius * cy->radius;
	side->a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
	side->b = 2.0f * ray.origin.x * ray.direction.x + 2.0f * ray.origin.y * ray.direction.y;
	side->c = ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y - 1.0f ;

	side->discriminant = side->b * side->b - 4.0f * side->a * side->c;
}

// Check if intersection lies within finite cylinder height
static void append_cy_side_hit(t_shape *cy,t_cy_geom *data, t_intersection *it, float t)
{
	float h;

	h = data->oc_axis + t * data->ray_axis;
	if (t > EPSILON && h >= -cy->half_h && h <= cy->half_h && it->count < 4)
		it->val[it->count++] = t;
}

// Solve quadratic and test valid intersections with cylinder side
static void add_cy_side_hits(t_shape *cy, t_quad *side, t_cy_geom *data, t_intersection *it)
{
	float t0;
	float t1;
	float sqrt_discrimimnant;

	if (fabsf(side->a) < EPSILON || side->discriminant < 0.0f)
		return;

	sqrt_discrimimnant = sqrtf(side->discriminant);
	t0 = (-side->b - sqrt_discrimimnant) / (2.0f * side->a);
	t1 = (-side->b + sqrt_discrimimnant) / (2.0f * side->a);

	append_cy_side_hit(cy, data, it, t0);
	append_cy_side_hit(cy, data, it, t1);
}

static void add_cy_caps(t_ray ray, t_shape *cy, t_intersection *it)
{
	float denom;
	float t;
	t_disk disk;

	denom = vector_dot(ray.direction, cy->axis);
	if (fabsf(denom) <= EPSILON)
		return;
	disk.radius = cy->radius;
	// bottom cap
	disk.center = vector_add(cy->normal.origin,
			vector_multiply(cy->axis, -cy->half_h));
	t = vector_dot(vector_substract(disk.center, ray.origin),
			cy->axis) / denom;
	add_cap_hit(ray, t, disk, it);

	// top cap
	disk.center = vector_add(cy->normal.origin,
			vector_multiply(cy->axis, cy->half_h));
	t = vector_dot(vector_substract(disk.center, ray.origin),
			cy->axis) / denom;
	add_cap_hit(ray, t, disk, it);
}

static void hit_cy(t_ray ray, t_shape *cy, t_intersection *intersection)
{
	t_cy_geom data;
	t_quad side;

	intersection->shape = cy;

	init_cy_data(ray, cy, &data);
	set_cy_quad(ray, cy, &data, &side);
	add_cy_side_hits(cy, &side, &data, intersection);
	add_cy_caps(ray, cy, intersection);
}

