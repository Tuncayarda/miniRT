#include "parser.h"
#include "entities.h"
#include "minirt.h"
#include "libft.h"
#include "util.h"

void	parse_sphere(scene *sc, char **args)
{
	sphere	s;

	ft_memset(&s, 0, sizeof(sphere));
	if (args && args[0] && args[1] && args[2] && args[3])
	{
		s.pos.x = ft_atof(args[1]);
		s.pos.y = ft_atof(ft_strchr(args[1], ',') + 1);
		s.pos.z = ft_atof(ft_strrchr(args[1], ',') + 1);
		s.dia = ft_atof(args[2]);
		s.color.r = ft_atof(args[3]);
		s.color.g = ft_atof(ft_strchr(args[3], ',') + 1);
		s.color.b = ft_atof(ft_strrchr(args[3], ',') + 1);
		parse_material(&s.mat, args);
		add_entity(sc, generate_entity(&s, ENT_SPHERE), ENT_SPHERE);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
