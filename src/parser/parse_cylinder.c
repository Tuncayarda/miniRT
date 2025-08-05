#include "minirt.h"
#include "entities.h"
#include "util.h"
#include "libft.h"
#include "parser.h"

void	parse_cylinder(scene *sc, char **args)
{
	cylinder	c;

	ft_memset(&c, 0, sizeof(cylinder));
	if (args && args[0] && args[1] && args[2] && args[3] && args[4] && args[5])
	{
		c.pos.x = ft_atof(args[1]);
		c.pos.y = ft_atof(ft_strchr(args[1], ',') + 1);
		c.pos.z = ft_atof(ft_strrchr(args[1], ',') + 1);
		c.axis.x = ft_atof(args[2]);
		c.axis.y = ft_atof(ft_strchr(args[2], ',') + 1);
		c.axis.z = ft_atof(ft_strrchr(args[2], ',') + 1);
		c.dia = ft_atof(args[3]);
		c.h = ft_atof(args[4]);
		c.color.r = ft_atof(args[5]);
		c.color.g = ft_atof(ft_strchr(args[5], ',') + 1);
		c.color.b = ft_atof(ft_strrchr(args[5], ',') + 1);
		parse_material(&c.mat, args);
		add_entity(sc, generate_entity(&c, ENT_CYLINDER), ENT_CYLINDER);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
