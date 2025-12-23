#include "minirt.h"

t_sphere	*sphere_new(t_vec3 *center, float radius)
{
	t_sphere *sp;
	sp = malloc(sizeof(t_sphere));
	if (!sp)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	sp->center = center;
	sp->radius = radius;
	return (sp);
}

int sphere_intersect(t_camera *cam, t_vec3 *ray, t_sphere *sphere)
{
	float b;
	float c;
	float discr;
	float dist_1; // dist before sphere
	//float dist_2; // dist after sphere
	t_vec3 *cam_sphere;

	dist_1 = 0;
	//dist_2 = 0;
	cam_sphere = vec_substr(cam->origin, sphere->center);
	b = 2 * (vec_dot(cam_sphere, ray));
	c = vec_dot(cam_sphere, cam_sphere) - (sphere->radius * sphere->radius);
	discr = (b * b) - (4 * c);
	free(cam_sphere);
	if(discr < 0)
		return (0); // no intersection with sphere
	dist_1 = ((b *(-1)) - sqrt(discr)) / 2; 
	//dist_2 = ((b *(-1)) + sqrt(discr)) / 2; 
	if(dist_1 > 0)
		return (1);
	return (0); 
	
}