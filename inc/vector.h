#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}			t_vec3;

t_vec3		*vec_new(float x, float y, float z);
t_vec3		*vec_substr(t_vec3 *vec1, t_vec3 *vec2);
float		vec_len(t_vec3 *vec);
void		vec_norm(t_vec3 *vec);
float		vec_dot(t_vec3 *vec1, t_vec3 *vec2);

#endif