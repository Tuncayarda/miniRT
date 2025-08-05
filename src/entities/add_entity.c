#include "minirt.h"
#include "libft.h"

void	add_entity(scene *sc, void *ent, ent_type type)
{
	size_t	n;
	entity	*new_ents;

	n = sc->ent_count + 1;
	new_ents = gc_manager(malloc(sizeof(entity) * n), MODE_ADD);
	if (!new_ents)
		return ;
	if (sc->ents)
		ft_memcpy(new_ents, sc->ents, sizeof(entity) * sc->ent_count);
	new_ents[n - 1].ent = ent;
	new_ents[n - 1].type = type;
	sc->ents = new_ents;
	sc->ent_count = n;
}
