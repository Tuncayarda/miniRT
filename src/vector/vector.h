#ifndef __VECTOR_H__
# define __VECTOR_H__

#define VECTOR_INIT (vec3){0, 0, 0}

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				vec3;

vec3	vec_add(vec3 a, vec3 b);
vec3	vec_add3(vec3 a, vec3 b, vec3 c);
vec3	vec_sub(vec3 a, vec3 b);
vec3	vec_scale(vec3 v, float s);
vec3	vec_norm(vec3 v);
vec3	vec_negate(vec3 v);
vec3	vec_cross(vec3 a, vec3 b);
float	vec_dot(vec3 a, vec3 b);
float	vec_length(vec3 v);

#endif