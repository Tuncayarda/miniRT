#include <math.h>
#include "render.h"

bool	get_closest(t_scene *sc, t_trace_var *var, t_ray r)
{
	size_t	i;

	i = 0;
	var->type = ENT_UNKNOWN;
	var->closest_i = -1;
	var->closest_t = INFINITY;
	while (i < sc->ent_count)
	{
		if (check_hit(sc, var, r, i))
		{
			var->closest_t = var->t;
			var->closest_i = i;
			var->type = sc->ents[i].type;
		}
		i++;
	}
	if (var->closest_i == -1)
		return (false);
	return (true);
}
