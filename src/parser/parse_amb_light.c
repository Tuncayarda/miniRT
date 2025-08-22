#include "parser.h"
#include "libft.h"
#include "util.h"

void	parse_amb_light(t_scene *sc, char **args)
{
	if (args && args[0] && args[1] && args[2])
	{
		sc->ambient.ratio = ft_atof(args[1]);
		sc->ambient.color.r = ft_atoi(args[2]);
		sc->ambient.color.g = ft_atoi(ft_strchr(args[2], ',') + 1);
		sc->ambient.color.b = ft_atoi(ft_strrchr(args[2], ',') + 1);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
