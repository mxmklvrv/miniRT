#include "minirt.h"

static t_intersection hit_sp(t_ray ray, t_shape *sp);
static t_intersection hit_cy(t_ray ray, t_shape *cy);
static t_intersection hit_pl(t_ray ray, t_shape *pl);

typedef struct s_cy_geom
{
    t_vec3 origin_to_ray; // vector from cy center to ray origin
    float ray_axis; // projection of ray direction on cy axis
    float oc_axis; // projection of origin_to_ray on cy axis
} t_cy_geom;

typedef struct s_cy_quad
{
    t_vec3 ray_perp; // ray direction component perpendicular to cy axis
    t_vec3 oc_perp; // origin_to_ray component perpendicular to cy axis
    float a;
    float b;
    float c;
    float disc;
} t_cy_quad;

typedef struct s_disk
{
    t_vec3 center;
    float radius;
} t_disk;

static void init_cy_data(t_ray ray, t_shape *cy, t_cy_geom *data);
static void set_cy_quad(t_ray ray, t_shape *cy, t_cy_geom *data, t_cy_quad *side);
static void append_cy_side_hit(t_shape *cy,t_cy_geom *data, t_intersection *it, float t);
static void add_cy_side_hits(t_shape *cy, t_cy_quad *side, t_cy_geom *data, t_intersection *it);
static void add_cy_caps(t_ray ray, t_shape *cy, t_intersection *it);
static void add_cap_hit(t_ray ray, float t, t_disk disk, t_intersection *it);

t_intersection get_intersection(t_ray ray, t_shape *shape)
{
    t_intersection intersection;

    intersection.count = 0;
    if (shape->obj_type == SP)
        intersection = hit_sp(ray, shape);
    else if (shape->obj_type == CY)
        intersection = hit_cy(ray, shape);
    else if (shape->obj_type == PL)
        intersection = hit_pl(ray, shape);
    return (intersection);
}

static t_intersection hit_sp(t_ray ray, t_shape *sp)
{
    float a;
    float b;
    float c;
    t_vec3 vector_to_sphere;
    float discriminant;
    t_intersection intersection;

    vector_to_sphere = vector_substract(ray.origin, sp->center);
    a = vector_dot(ray.direction, ray.direction);
    b = 2 * vector_dot(ray.direction, vector_to_sphere);
    c = vector_dot(vector_to_sphere, vector_to_sphere) - sp->diameter * sp->diameter / 4;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        intersection.count = 0;
    else // Find intersection:
    {
        intersection.count = 2;
        intersection.val[0] = (-b - sqrtf(discriminant)) / (2 * a);
        intersection.val[1] = (-b + sqrtf(discriminant)) / (2 * a);
    }
    intersection.shape = sp;
    return (intersection);
}

static void add_cap_hit(t_ray ray, float t, t_disk disk, t_intersection *it)
{
    t_vec3 hit_point;
    t_vec3 to_center;

    if (t <= EPSILON || it->count >= 4)
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
static void set_cy_quad(t_ray ray, t_shape *cy, t_cy_geom *data, t_cy_quad *side)
{
    side->ray_perp = vector_substract(ray.direction,
                                      vector_multiply(cy->axis, data->ray_axis));

    side->oc_perp = vector_substract(data->origin_to_ray,
                                     vector_multiply(cy->axis, data->oc_axis));

    side->a = vector_dot(side->ray_perp, side->ray_perp);
    side->b = 2.0f * vector_dot(side->ray_perp, side->oc_perp);
    side->c = vector_dot(side->oc_perp, side->oc_perp) - cy->radius * cy->radius;

    side->disc = side->b * side->b - 4.0f * side->a * side->c;
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
static void add_cy_side_hits(t_shape *cy, t_cy_quad *side, t_cy_geom *data, t_intersection *it)
{
    float t0;
    float t1;
    float sqrt_disc;

    if (fabsf(side->a) < EPSILON || side->disc < 0.0f)
        return;

    sqrt_disc = sqrtf(side->disc);
    t0 = (-side->b - sqrt_disc) / (2.0f * side->a);
    t1 = (-side->b + sqrt_disc) / (2.0f * side->a);

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

static t_intersection hit_cy(t_ray ray, t_shape *cy)
{
    t_intersection it;
    t_cy_geom data;
    t_cy_quad side;

    it.count = 0;
    it.shape = cy;

    init_cy_data(ray, cy, &data);
    set_cy_quad(ray, cy, &data, &side);
    add_cy_side_hits(cy, &side, &data, &it);
    add_cy_caps(ray, cy, &it);
    return (it);
}

static t_intersection hit_pl(t_ray ray, t_shape *pl)
{
    float denominator;
    t_intersection intersection;

    denominator = vector_dot(ray.direction, pl->normal.direction);
    if (fabsf(denominator) < EPSILON) // cam and plane (almost or fully) parallel
        intersection.count = 0;
    else // Find intersection:
    {
        intersection.count = 1;
        intersection.val[0] = vector_dot(vector_substract(pl->normal.origin, ray.origin), pl->normal.direction) / denominator;
    }
    intersection.shape = pl;
    return (intersection);
}
