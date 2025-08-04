#include "entities.h"
#include "minirt.h"
#include "libft.h"
#include "gc.h"

void	add_light(scene *sc, vec3 loc, color color, float ratio)
{
	size_t	n;
	light	*new_lights;

	n = sc->light_count + 1;
	new_lights = gc_track(&sc->gc, malloc(sizeof(light) * n));
	if (!new_lights)
		return ;
	if (sc->lights)
		ft_memcpy(new_lights, sc->lights, sizeof(light) * sc->light_count);
	new_lights[n - 1].loc = loc;
	new_lights[n - 1].color = color;
	new_lights[n - 1].ratio = ratio;
	sc->lights = new_lights;
	sc->light_count = n;
}