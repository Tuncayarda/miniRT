#include "entities.h"
#include "gc.h"
#include "libft.h"

sphere	*generate_sphere(sphere *s)
{
	sphere	*ret;

	ret = gc_manager(malloc(sizeof(sphere)), MODE_ADD);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s, sizeof(sphere));
	return (ret);
}
