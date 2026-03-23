#include "minirt.h"

bool	is_in_light(t_scene *scene, t_ray light_ray);

/* Material properties:
 * ambient constant = 0.1; from file
 * diffuse constant = 0.9; default, all have the same
 * specular constant = 0.9; default, all have the same
 * shininess = 32.0. default, all have the same
 * Light properties:
 * intencity - from file;
 */
//int	lighting(t_scene *scene, t_intersection intersection, t_ray ray)
//{
//	int	color;
//	int	ambient_color;
//	int	diffuse_color;
//	int	specular_color;
//	float	diffuse_light;
//	float	specular_light;
//	t_vec3	point;
//	t_vec3	light_vector;
//	t_ray	light_ray;
//	float	light_angle;
//	t_vec3	normal_vector;
//	t_vec3	reflect_vector;
//	float	reflect_angle;
//	float	shininess;

//	color = 0;
	
//	diffuse_light = 0;
//	specular_light = 0;
//	point = get_ray_point(ray, get_closest_hit(intersection));
//	light_vector = vector_normalize(vector_substract(scene->light.pos, point));
//	light_ray.origin = point;
//	light_ray.direction = light_vector;
//	//if (is_in_light(scene, light_ray))
//	//{
//		normal_vector = get_normal(intersection.shape, point);
//		light_angle = vector_dot(light_vector, normal_vector);
//		if (light_angle >= 0)
//		{
//			diffuse_light = scene->light.bright * light_angle;
//			reflect_vector = vector_reflect(vector_negate(light_vector), normal_vector);
//			reflect_angle = vector_dot(reflect_vector, vector_negate(ray.direction));
//			if (reflect_angle >= 0)
//			{
//				shininess = powf(reflect_angle, 64.0);//material reflective properties
//				specular_light = scene->light.bright * shininess;
//			}
//		}
//	//}

//	//Mix object and light color
//	color = color_mix(intersection.shape->color, scene->light.color,
//		scene->light.bright * scene->ambient.amb);
//	//Mix background and object based on light
//	ambient_color = color_mix(scene->ambient.color, color, scene->ambient.amb);
//	diffuse_color = color_mix(scene->ambient.color, color, diffuse_light);
//	specular_color = color_mix(scene->ambient.color, scene->light.color, specular_light);
//	//color = color_add(color_add(ambient_color, diffuse_color), specular_color);

//	color = color_mix(color, scene->ambient.color, scene->ambient.amb);
//	color = color_mix(color, scene->light.color, diffuse_light);
//	//color = color_mix(color, scene->light.color, specular_light);
//	color = color_add(color, color_multiply(scene->light.color, specular_light));
//	return (color);
//}

int	lighting(t_scene *scene, t_intersection intersection, t_ray ray)
{
	int	color;
	int	ambient_color;
	int	diffuse_color;
	int	specular_color;
	float	diffuse_light;
	float	specular_light;
	t_vec3	point;
	t_vec3	light_vector;
	t_ray	light_ray;
	float	light_angle;
	t_vec3	normal_vector;
	t_vec3	reflect_vector;
	float	reflect_angle;
	float	shininess;

	color = 0;
	
	diffuse_light = 0;
	specular_light = 0;
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
			diffuse_light = scene->light.bright * light_angle;
			reflect_vector = vector_reflect(vector_negate(light_vector), normal_vector);
			reflect_angle = vector_dot(reflect_vector, vector_negate(ray.direction));
			if (reflect_angle >= 0)
			{
				shininess = powf(reflect_angle, 64.0);//material reflective properties
				specular_light = scene->light.bright * shininess;
			}
		}
	//}

	//Mix object and light color
	color = color_mix(intersection.shape->color, scene->light.color,
		scene->light.bright * scene->ambient.amb);
	//Mix background and object based on light
	ambient_color = color_mix(scene->ambient.color, color, scene->ambient.amb);
	diffuse_color = color_mix(scene->ambient.color, color, diffuse_light);
	specular_color = color_mix(scene->ambient.color, scene->light.color, specular_light);
	//color = color_add(color_add(ambient_color, diffuse_color), specular_color);

	color = color_mix(color, scene->ambient.color, scene->ambient.amb);
	color = color_mix(color, scene->light.color, diffuse_light);
	//color = color_mix(color, scene->light.color, specular_light);
	color = color_add(color, color_multiply(scene->light.color, specular_light));
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

