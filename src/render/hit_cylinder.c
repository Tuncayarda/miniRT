#include <math.h>
#include "entities.h"
#include "vector.h"
#include "util.h"
#include "render.h"

float	define_a(t_cylinder *cy, t_ray r)
{
	return (
		vec_dot(r.direction, r.direction)
		- powf(vec_dot(r.direction, vec_norm(cy->axis)), 2));
}

float	define_b(t_cylinder *cy, t_ray r)
{
	return (
		2 * (vec_dot(r.direction, vec_sub(r.origin, cy->pos))
			- (vec_dot(r.direction, vec_norm(cy->axis))
				* vec_dot(vec_sub(r.origin, cy->pos), vec_norm(cy->axis)))));
}

float	define_c(t_cylinder *cy, t_ray r)
{
	return (
		vec_dot(vec_sub(r.origin, cy->pos), vec_sub(r.origin, cy->pos))
		- powf(vec_dot(vec_sub(r.origin, cy->pos), vec_norm(cy->axis)), 2)
		- powf(cy->dia * 0.5f, 2));
}

bool	hit_cylinder(t_cylinder *cy, t_ray r, float *t_hit)
{
	t_vec3	p;
	float	s_top;
	float	s_bot;

	if (!solve_quadratic(
			define_a(cy, r),
			define_b(cy, r),
			define_c(cy, r),
			t_hit))
		return (false);
	p = vec_add(r.origin, vec_scale(r.direction, *t_hit));
	s_top = vec_dot(vec_sub(p, cy->top.pos), cy->top.axis);
	s_bot = vec_dot(vec_sub(p, cy->bottom.pos), cy->bottom.axis);
	if (!(s_top <= 0.0f && s_bot <= 0.0f))
		return (false);
	return (true);
}
