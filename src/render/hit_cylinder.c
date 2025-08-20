#include <math.h>
#include "entities.h"
#include "vector.h"
#include "util.h"
#include "render.h"

bool	hit_cylinder(cylinder *cy, ray r, float *t_hit)
{
	float	a;
	float	b;
	float	c;


	a = vec_dot(r.direction, r.direction) - powf(vec_dot(r.direction, vec_norm(cy->axis)), 2);
	b = 2 * (vec_dot(r.direction, vec_sub(r.origin, cy->pos)) - (vec_dot(r.direction ,vec_norm(cy->axis)) * vec_dot(vec_sub(r.origin, cy->pos), vec_norm(cy->axis))));
	c = vec_dot(vec_sub(r.origin, cy->pos), vec_sub(r.origin, cy->pos)) - powf(vec_dot(vec_sub(r.origin, cy->pos), vec_norm(cy->axis)), 2) - powf(cy->dia * 0.5f , 2);

	if (!solve_quadratic(a, b, c, t_hit))
		return (false);

	vec3 P = vec_add(r.origin, vec_scale(r.direction, *t_hit));
	float s_top = vec_dot(vec_sub(P, cy->top.pos), cy->top.axis);
	float s_bot = vec_dot(vec_sub(P, cy->bottom.pos), cy->bottom.axis);

	if (!(s_top <= 0.0f && s_bot <= 0.0f))
		return (false);

	return (true);
}
