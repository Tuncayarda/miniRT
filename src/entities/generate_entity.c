#include "entities.h"
#include "gc.h"
#include "libft.h"

void	*generate_entity(void *src, ent_type type)
{
	size_t	size;

	if (type == ENT_SPHERE)
		size = sizeof(sphere);
	else if (type == ENT_PLANE)
		size = sizeof(plane);
	else if (type == ENT_CYLINDER)
		size = sizeof(cylinder);
	else if (type == ENT_CIRCLE)
		size = sizeof(circle);
	else
		return (NULL);

	void *ret = gc_manager(malloc(size), MODE_ADD);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, src, size);
	return (ret);
}
