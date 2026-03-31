#include "minirt.h"

static bool	is_in_shadow(t_scene *scene, t_ray normal_ray, float *distance);
static int	get_diffuse_color(t_light light, float light_angle);
static int	get_specular_color(t_light light, t_vec3 light_vector, t_vec3 normal_vector, t_ray ray);

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
	int		color;
	t_ray	normal;
	t_vec3	light_vector;
	float	light_angle;
	int		ambient;
	int		diffuse;
	int		specular;
	float	distance;
	t_light	current_light;

	ambient = color_multiply(scene->ambient.color, scene->ambient.amb);
	color = color_mix_light(intersection.shape->color, ambient);
	normal.origin = get_ray_point(ray, get_closest_hit(intersection));
	normal.direction = get_normal(intersection.shape, normal.origin);
	normal.origin = vector_add(normal.origin, vector_multiply(normal.direction, EPSILON));

	
	diffuse = 0;
	specular = 0;
	//Can add while for multiple lights
	current_light = scene->light;
	light_vector = vector_normalize(vector_substract(current_light.pos, normal.origin));
	light_angle = vector_dot(light_vector, normal.direction);
	if (light_angle < 0 || is_in_shadow(scene, new_ray(normal.origin, light_vector), &distance))
		return (color);
	if (distance < 1)
		distance = 1;
	current_light.bright /= distance / 5;
	diffuse = color_add(diffuse, get_diffuse_color(current_light, light_angle));
	specular = color_add(specular, get_specular_color(current_light, light_vector, 
		normal.direction, ray));
	


	//Applying all lights to object color
	color = color_mix_light(intersection.shape->color, color_add(ambient, diffuse));
	color = color_add(color, specular);
	return (color);
}

static int	get_diffuse_color(t_light light, float light_angle)
{
	return (color_mix(0, light.color, light.bright * light_angle));
}

static int	get_specular_color(t_light light, t_vec3 light_vector, t_vec3 normal_vector, t_ray ray)
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

static bool	is_in_shadow(t_scene *scene, t_ray normal_ray, float *distance)
{
	t_olist			*obj_list;
	t_intersection	closest;

	*distance = vector_magnitude(vector_substract(scene->light.pos, normal_ray.origin));
	closest.count = 0;
	obj_list = scene->obj_list;
	while (obj_list)
	{
		find_closest_intersection(normal_ray, obj_list->shape, &closest);
		obj_list = obj_list->next;
	}
	if (closest.count > 0 && get_closest_hit(closest) < *distance - EPSILON)
		return (true);
	return (false);
}

