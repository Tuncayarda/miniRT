#include <math.h>
#include "util.h"
#include "entities.h"
#include "render.h"
#include "color.h"
#include "libft.h"

t_color	trace_ray(t_scene *sc, t_ray r)
{
	t_trace_var	var;

	ft_bzero(&var.total_diffuse, sizeof(t_color));
	ft_bzero(&var.total_specular, sizeof(t_color));
	if (!get_closest(sc, &var, r))
		return (color_scale(sc->ambient.color, sc->ambient.ratio));
	define_closest(sc, &var, r);
	compute_diffuse(sc, &var);
	if (var.mat.has_spc)
		compute_specular(sc, &var, r);
	return (color_add(var.ambient,
			color_add(var.total_diffuse, var.total_specular)));
}
