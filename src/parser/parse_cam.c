#include <math.h>
#include "parser.h"
#include "libft.h"
#include "vector.h"
#include "util.h"

void	parse_cam(scene *sc, char **args)
{
	if (args && args[0] && args[1] && args[2] && args[3])
	{
		sc->cam.pos.x = ft_atof(args[1]);
		sc->cam.pos.y = ft_atof(ft_strchr(args[1], ',') + 1);
		sc->cam.pos.z = ft_atof(ft_strrchr(args[1], ',') + 1);
		sc->cam.dir.x = ft_atof(args[2]);
		sc->cam.dir.y = ft_atof(ft_strchr(args[2], ',') + 1);
		sc->cam.dir.z = ft_atof(ft_strrchr(args[2], ',') + 1);
		sc->cam.fov = ft_atoi(args[3]);
		sc->cam.dir = vec_norm(sc->cam.dir);
		sc->cam.half_height = tanf((sc->cam.fov * M_PI / 180.0f) / 2.0f);
		sc->cam.half_width  = sc->cam.half_height * ASPECT_RATIO;
		sc->cam.right = vec_norm(vec_cross(sc->cam.dir, WORLD_UP));
		sc->cam.up    = vec_norm(vec_cross(sc->cam.right, sc->cam.dir));
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
