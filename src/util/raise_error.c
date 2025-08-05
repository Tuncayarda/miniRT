#include "util.h"
#include "libft.h"

void	raise_error(scene *sc, const char *msg)
{
	(void)sc;
	gc_manager(NULL, MODE_FREE);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(1);
}