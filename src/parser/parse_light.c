#include "parser.h"
#include "vector.h"
#include "entities.h"
#include "util.h"
#include "libft.h"

void	parse_light(scene *sc, char **args)
{
	vec3	loc;
	color	color;
	float	ratio;

	if (args && args[0] && args[1] && args[2] && args[3])
	{
		loc.x = ft_atof(args[1]);
		loc.y = ft_atof(ft_strchr(args[1], ',') + 1);
		loc.z = ft_atof(ft_strrchr(args[1], ',') + 1);
		ratio = ft_atof(args[2]);
		color.r = ft_atoi(args[3]);
		color.g = ft_atoi(ft_strchr(args[3], ',') + 1);
		color.b = ft_atoi(ft_strrchr(args[3], ',') + 1);
		add_light(sc, loc, color, ratio);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
