#include "entities.h"
#include "minirt.h"
#include "libft.h"
#include "gc.h"

void	add_light(scene *sc, light l)
{
	size_t	n;
	light	*new_lights;

	n = sc->light_count + 1;
	new_lights = gc_manager(malloc(sizeof(light) * n), MODE_ADD);
	if (!new_lights)
		return ;
	if (sc->lights)
		ft_memcpy(new_lights, sc->lights, sizeof(light) * sc->light_count);
	new_lights[n - 1] = l;
	sc->lights = new_lights;
	sc->light_count = n;
}