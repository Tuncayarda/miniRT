#include <math.h>
#include "entities.h"
#include "vector.h"
#include "util.h"
#include "render.h"

bool	hit_circle(t_circle *c, t_ray r, float *t_hit)
{
	t_vec3	n;
	float	denom;
	float	t;
	t_vec3	p;
	t_vec3	v;

	n = vec_norm(c->axis);
	denom = vec_dot(n, r.direction);
	if (fabs(denom) < EPSILON)
		return (false);
	t = vec_dot(vec_sub(c->pos, r.origin), n) / denom;
	if (t <= 1e-4f)
		return (false);
	*t_hit = t;
	p = vec_add(r.origin, vec_scale(r.direction, t));
	v = vec_sub(p, c->pos);
	if (vec_length(v) > c->radius)
		return (false);
	return (true);
}
