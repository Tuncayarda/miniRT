#include <math.h>
#include "render.h"
#include "entities.h"

static bool	solve_quadratic(float a, float b, float c, float *t)
{
	float	discriminant;
	float	temp;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	temp = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (temp < 0)
		temp = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (temp < 0)
		return (false);
	*t = temp;
	return (true);
}

bool	hit_sphere(sphere *s, ray r, float *t_hit)
{
	vec3	oc;
	float	radius;
	float	a;
	float	b;
	float	c;

	oc = vec_sub(r.origin, s->pos);
	radius = s->dia / 2.0f;
	a = vec_dot(r.direction, r.direction);
	b = 2.0f * vec_dot(oc, r.direction);
	c = vec_dot(oc, oc) - radius * radius;
	if (!solve_quadratic(a, b, c, t_hit))
		return (false);
	return (true);
}
