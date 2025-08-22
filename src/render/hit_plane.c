#include <math.h>
#include "entities.h"
#include "vector.h"
#include "util.h"
#include "render.h"

bool	hit_plane(t_plane *pl, ray r, float *t_hit)
{
	t_vec3	n;
	float	denom;
	float	t;

	n = vec_norm(pl->axis);
	denom = vec_dot(n, r.direction);
	if (fabs(denom) < 1e-6f)
		return (false);

	t = vec_dot(vec_sub(pl->pos, r.origin), n) / denom;
	if (t <= 1e-4f)
		return (false);
	
	*t_hit = t;
	return (true);
}
