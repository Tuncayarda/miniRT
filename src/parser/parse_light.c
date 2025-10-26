#include "parser.h"
#include "vector.h"
#include "entities.h"
#include "util.h"
#include "libft.h"

void	parse_light(t_scene *sc, char **args)
{
	t_light	l;

	ft_memset(&l, 0, sizeof(t_light));
	if (args && args[0] && args[1] && args[2] && args[3])
	{
		l.pos.x = ft_atof(args[1]);
		l.pos.y = ft_atof(ft_strchr(args[1], ',') + 1);
		l.pos.z = ft_atof(ft_strrchr(args[1], ',') + 1);
		l.ratio = ft_atof(args[2]);
		l.color.r = ft_atoi(args[3]);
		l.color.g = ft_atoi(ft_strchr(args[3], ',') + 1);
		l.color.b = ft_atoi(ft_strrchr(args[3], ',') + 1);
		add_light(sc, l);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
