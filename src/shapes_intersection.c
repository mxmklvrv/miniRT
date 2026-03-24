#include "minirt.h"

static t_intersection hit_sp(t_ray ray, t_shape *sp);
static t_intersection hit_cy(t_ray ray, t_shape *cy);
static t_intersection hit_pl(t_ray ray, t_shape *pl);

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

static t_intersection hit_cy(t_ray ray, t_shape *cy)
{
    t_intersection intersection;
    float a;
    float b;
    float c; 
    float discriminant;

    a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z; // is the ray moves towards cylinder side
    if(fabsf(a) < EPSILON)
    {
        intersection.count = 0;
        intersection.shape = cy;
        return (intersection);
    }
        
    b = 2 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z); // is the ray moving towards or away 
    c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1; // distance from cylinder axis
    discriminant = b * b - 4 * a * c; // dose it intersect ? 
    if(discriminant < 0)
        intersection.count = 0;
    else 
    {
        intersection.count = 2;
        intersection.val[0] = (-b - sqrtf(discriminant)) / (2 * a);
        intersection.val[1] = (-b + sqrtf(discriminant)) / (2 * a);
    }
    intersection.shape = cy;
    return (intersection);
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
