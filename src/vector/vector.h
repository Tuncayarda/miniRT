#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_add3(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3	vec_sub(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 v, float s);
t_vec3	vec_norm(t_vec3 v);
t_vec3	vec_negate(t_vec3 v);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
t_vec3	vec_gen(float x, float y, float z);
float	vec_dot(t_vec3 a, t_vec3 b);
float	vec_length(t_vec3 v);

#endif