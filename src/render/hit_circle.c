#include <math.h>
#include "entities.h"
#include "vector.h"
#include "util.h"
#include "render.h"

bool	hit_circle(t_circle *c, ray r, float *t_hit)
{
	t_vec3	n;
	float	denom;
	float	t;

	n = vec_norm(c->axis);
	denom = vec_dot(n, r.direction);
	if (fabs(denom) < EPSILON)
		return (false);

	t = vec_dot(vec_sub(c->pos, r.origin), n) / denom;
	if (t <= 1e-4f)
		return (false);

	*t_hit = t;
	t_vec3	P = vec_add(r.origin, vec_scale(r.direction, t));
	t_vec3	v = vec_sub(P, c->pos);
	if (vec_length(v) > c->radius)
		return (false);
	return (true);
}
