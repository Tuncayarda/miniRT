#include "util.h"
#include "libft.h"

void	raise_error(scene *sc, const char *msg)
{
	gc_free_all(&sc->gc);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(1);
}