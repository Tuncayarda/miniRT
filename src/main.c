#include "minirt.h"
#include "parser.h"
#include "libft.h"
#include "debug.h"

int	main(int ac, char **av)
{
	scene	sc;

	ft_memset(&sc, 0, sizeof(scene));

	parser(&sc, ac, av);
	print_scene_debug(&sc);
	gc_manager(NULL, MODE_FREE);
	return (0);
}
