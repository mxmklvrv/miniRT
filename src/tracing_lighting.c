#include "minirt.h"

static bool	is_in_shadow(t_scene *scene, t_light light, t_ray light_ray,
	float *distance);
static int	get_diffuse_color(t_light light, float light_angle);
static int	get_specular_color(t_light light, t_vec3 light_vector,
	t_vec3 normal_vector, t_ray ray);
static void	add_current_light(t_light light, t_lighting *lighting,
	t_scene *scene, t_ray ray);

/* Material properties:
 * ambient constant; - we don't have
 * diffuse constant; - we don't have
 * specular constant; - we don't have
 * shininess (2.0, 4.0, 8.0, 16.0, 32.0... 200.0); the bigger the shininess -
 * the smaller and more defined is specular dot.
 * 
 * Light properties:
 * intencity; - from file
 * amb - intencity of ambient light;
 * bright - intencity of dot light.
 */
int	lighting(t_scene *scene, t_intersection intersection, t_ray ray)
{
	int			color;
	t_lighting	lighting;
	t_llist		*llist;

	lighting.ambient = color_multiply(scene->ambient.color, scene->ambient.amb);
	color = color_mix_light(intersection.shape->color, lighting.ambient);
	lighting.normal.origin = get_ray_point(ray, get_closest_hit(intersection));
	lighting.normal.direction = get_normal(intersection.shape,
		lighting.normal.origin);
	lighting.normal.origin = vector_add(lighting.normal.origin, 
		vector_multiply(lighting.normal.direction, EPSILON));
	lighting.diffuse = 0;
	lighting.specular = 0;
	llist = scene->light_list;
	while (llist)
	{
		add_current_light(*llist->light, &lighting, scene, ray);
		llist = llist->next;
	}
	color = color_mix_light(intersection.shape->color,
		color_add(lighting.ambient, lighting.diffuse));
	color = color_add(color, lighting.specular);
	return (color);
}

static void	add_current_light(t_light light, t_lighting *lighting,
	t_scene *scene, t_ray ray)
{
	t_vec3		light_vector;
	float		light_angle;
	float		distance;
	t_lighting	current;

	light_vector = vector_normalize(
		vector_substract(light.pos, lighting->normal.origin));
	light_angle = vector_dot(light_vector, lighting->normal.direction);
	if (is_in_shadow(scene, light, 
		new_ray(lighting->normal.origin, light_vector), &distance))
		return ;
	if (distance < 1)
		distance = 1;
	light.bright /= distance / 5;
	current.diffuse = get_diffuse_color(light, light_angle);
	current.specular = get_specular_color(light, light_vector, 
		lighting->normal.direction, ray);
	lighting->diffuse = color_add(lighting->diffuse, current.diffuse);
	lighting->specular = color_add(lighting->specular, current.specular);
}

static int	get_diffuse_color(t_light light, float light_angle)
{
	return (color_mix(0, light.color, light.bright * light_angle));
}

static int	get_specular_color(t_light light, t_vec3 light_vector,
	t_vec3 normal_vector, t_ray ray)
{
	t_vec3	reflect_vector;
	float	reflect_angle;
	float	shininess;

	reflect_vector = vector_reflect(vector_negate(light_vector), normal_vector);
	reflect_angle = vector_dot(reflect_vector, vector_negate(ray.direction));
	if (reflect_angle < 0)
		return (0);
	shininess = powf(reflect_angle, 64.0);//material reflective properties
	return (color_mix(0, light.color, light.bright * shininess));
}

static bool	is_in_shadow(t_scene *scene, t_light light, t_ray light_ray,
	float *distance)
{
	t_olist			*obj_list;
	t_intersection	closest;

	*distance = vector_magnitude(vector_substract(light.pos, light_ray.origin));
	closest.count = 0;
	obj_list = scene->obj_list;
	while (obj_list)
	{
		find_closest_intersection(light_ray, obj_list->shape, &closest);
		obj_list = obj_list->next;
	}
	if (closest.count > 0 && get_closest_hit(closest) < *distance - EPSILON)
		return (true);
	return (false);
}
