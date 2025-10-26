#include <math.h>
#include "util.h"
#include "entities.h"
#include "render.h"
#include "color.h"
#include "libft.h"

void	compute_specular(t_scene *sc, t_trace_var *var, t_ray r)
{
	var->li = 0;
	while (var->li < sc->light_count)
	{
		if (is_reachable(sc, var, var->li))
		{
			var->spc.l = vec_norm(vec_sub(sc->lights[var->li].pos, var->hit_p));
			var->spc.v = vec_norm(vec_scale(r.direction, -1.0f));
			var->spc.nl = vec_dot(var->normal, var->spc.l);
			var->spc.r = vec_norm(vec_sub(vec_scale(var->normal, 2.0f
							* var->spc.nl), var->spc.l));
			if (var->spc.nl > 0)
			{
				var->spc.spc_term = powf(fmax(0, vec_dot(var->spc.r, var->spc.v)),
						var->mat.shininess);
				var->spc.spc_int = var->mat.specular_strength * var->spc.spc_term
					* sc->lights[var->li].ratio;
				var->specular = color_scale(sc->lights[var->li].color,
						var->spc.spc_int);
				var->total_specular = color_add(var->total_specular, var->specular);
			}
		}
		
		var->li++;
	}
}
