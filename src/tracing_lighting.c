#include "minirt.h"

bool	is_in_light(t_scene *scene, t_ray light_ray);

/* Material properties:
 * ambient_lighting = 0.1; from file
 * diffuse_lighting = 0.9; from file
 * specular_lighting = 0.9; default, all have the same
 * shininess = 32.0. default, all have the same
 */
int	lighting(t_scene *scene, t_intersection intersection, t_ray ray)
{
	int	color;
	float	ambient_lighting;
	float	diffuse_lighting;
	float	specular_lighting;
	t_vec3	point;
	t_vec3	light_vector;
	t_ray	light_ray;
	float	light_angle;
	t_vec3	normal_vector;
	t_vec3	reflect_vector;
	float	reflect_angle;
	float	shininess;

	color = color_mix(intersection.shape->color, scene->light.color, scene->light.bright);
	ambient_lighting = color_mix(color, scene->ambient.color, scene->ambient.amb);
	diffuse_lighting = 0;
	specular_lighting = 0;
	point = get_ray_point(ray, get_closest_hit(intersection));
	light_vector = vector_normalize(vector_substract(scene->light.pos, point));
	light_ray.origin = point;
	light_ray.direction = light_vector;
	//if (is_in_light(scene, light_ray))
	//{
		normal_vector = get_normal(intersection.shape, point);
		light_angle = vector_dot(light_vector, normal_vector);
		if (light_angle >= 0)
		{
			diffuse_lighting = color_mix(color, scene->light.color, light_angle * scene->light.bright);
			diffuse_lighting = color_mix(scene->ambient.color, diffuse_lighting, light_angle);
			reflect_vector = vector_reflect(vector_negate(light_vector), normal_vector);
			reflect_angle = vector_dot(reflect_vector, vector_negate(ray.direction));
			if (reflect_angle >= 0)
			{
				shininess = powf(reflect_angle, 32.0);
				specular_lighting = color_multiply(scene->light.color, 0.9 * shininess);
			}
		}
	//}
	color = color_add(color_add(ambient_lighting, diffuse_lighting), specular_lighting);
	return (color);
}

bool	is_in_light(t_scene *scene, t_ray light_ray)
{
	t_olist			*obj_list;
	t_intersection	closest;

	closest.count = 0;
	obj_list = scene->obj_list;
	while (obj_list)
	{
		find_closest_intersection(light_ray, obj_list->shape, &closest);
		obj_list = obj_list->next;
	}
	if (closest.count > 0 && get_closest_hit(closest) < vector_magnitude(
		vector_substract(scene->light.pos, light_ray.origin)))
		return (false);
	return (true);
}

