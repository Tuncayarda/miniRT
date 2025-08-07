#include <math.h>
#include "render.h"

color	trace_ray(scene *sc, ray r)
{
	sphere	*s;
	size_t	i;
	color	rtn;
	float	t;
	float	closest;

	closest = INFINITY;
	rtn.r = sc->ambient.color.r * sc->ambient.ratio;
	rtn.g = sc->ambient.color.g * sc->ambient.ratio;
	rtn.b = sc->ambient.color.b * sc->ambient.ratio;
	i = 0;
	while (i < sc->ent_count)
	{
		if (sc->ents[i].type == ENT_SPHERE)
		{
			s = (sphere *)sc->ents[i].ent;
			if (hit_sphere(sc->ents[i].ent, r, &t) && t < closest)
			{
				closest = t;
				rtn = s->color;
			}
		}
		i++;
	}
	return (rtn);
}
