#include <math.h>
#include "util.h"
#include "entities.h"
#include "render.h"
#include "color.h"
#include "libft.h"

void	compute_specular(t_scene *sc, trace_var *var, ray r)
{
	var->li = 0;
	if (var->mat.has_spc)
	{
		while (var->li < sc->light_count)
		{
			t_vec3	N = var->normal;
			t_vec3	L = vec_norm(vec_sub(sc->lights[var->li].pos, var->hit_p));
			t_vec3	V = vec_norm(vec_scale(r.direction, -1.0f));
			float	NL = vec_dot(N, L);
			t_vec3	R = vec_norm(vec_sub(vec_scale(N, 2.0f * NL), L));
			float	specular_int;
			float	spec_term;
			if (NL > 0)
			{
				spec_term = powf(fmax(0, vec_dot(R, V)), var->mat.shininess);
				specular_int = var->mat.specular_strength * spec_term * sc->lights[var->li].ratio;
				var->specular = color_scale(sc->lights[var->li].color, specular_int);
				var->total_specular = color_add(var->total_specular, var->specular);
			}
			var->li++;
		}	
	}
}

t_color	trace_ray(t_scene *sc, ray r)
{
	trace_var var;

	ft_memset(&var, 0, sizeof(trace_var));
	if (!get_closest(sc, &var, r))
		return (color_scale(sc->ambient.color, sc->ambient.ratio));
	define_closest(sc , &var, r);
	compute_diffuse(sc, &var);
	compute_specular(sc, &var, r);

	return (color_add(var.ambient, color_add(var.total_diffuse, var.total_specular)));
}
