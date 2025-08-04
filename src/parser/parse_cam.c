#include "parser.h"
#include "libft.h"
#include "util.h"

void	parse_cam(scene *sc, char **args)
{
	if (args && args[0] && args[1] && args[2] && args[3])
	{
		sc->cam.loc.x = ft_atof(args[1]);
		sc->cam.loc.y = ft_atof(ft_strchr(args[1], ',') + 1);
		sc->cam.loc.z = ft_atof(ft_strrchr(args[1], ',') + 1);
		sc->cam.dir.x = ft_atof(args[2]);
		sc->cam.dir.y = ft_atof(ft_strchr(args[2], ',') + 1);
		sc->cam.dir.z = ft_atof(ft_strrchr(args[2], ',') + 1);
		sc->cam.fov = ft_atoi(args[3]);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
