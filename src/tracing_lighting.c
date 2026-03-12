#include "minirt.h"

/* Material properties:
 * ambient = 0.1;
 * diffuse = 0.9;
 * specular = 0.9;
 * shininess = 200.0.
 */
int	lighting(t_light light, t_ambient background, t_intersection intersection, t_ray ray)
{
	int	color;
	float	ambient;
	float	diffuse;
	float	specular;
	t_vec3	point;
	t_vec3	light_vector;
	float	light_angle;
	t_vec3	normal_vector;
	t_vec3	reflect_vector;
	float	reflect_angle;
	float	shininess;

	color = intersection.shape->color;//color_mix(intersection.shape->color, 1, light.color, light.bright);
	point = get_ray_point(ray, get_closest_hit(intersection));
	light_vector = vector_normalize(vector_substract(light.pos, point));
	ambient = color_mix(color, 1, background.color, background.amb);
	normal_vector = get_normal(intersection.shape, point);
	light_angle = vector_dot(light_vector, normal_vector);
	if (light_angle < 0)
	{
		diffuse = 0;
		specular = 0;
	}
	else
	{
		diffuse = color_multiply(color, 0.9 * light_angle);
		reflect_vector = vector_reflect(vector_negate(light_vector), normal_vector);
		reflect_angle = vector_dot(reflect_vector, ray.direction);
		if (reflect_angle < 0 || is_equalf(reflect_angle, 0))
			specular = 0;
		else
		{
			shininess = powf(reflect_angle, 200.0);
			specular = light.bright * 0.9 * shininess;
		}
	}
	color = color_add(ambient, color_add(diffuse, specular));
	return (color);
}



