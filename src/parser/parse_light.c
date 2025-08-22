#include "parser.h"
#include "vector.h"
#include "entities.h"
#include "util.h"
#include "libft.h"

static void	parse_specs(t_light	*l, char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "dir:", 4) == 0)
		{
			l->dir.x = ft_atof(args[i] + 4);
			l->dir.y = ft_atoi(ft_strchr(args[i] + 4, ',') + 1);
			l->dir.z = ft_atoi(ft_strrchr(args[i], ',') + 1);
			l->type = LIGHT_SPOT;
		}
		else if (ft_strncmp(args[i], "ang:", 4) == 0)
		{
			l->angle = ft_atof(args[i] + 4);
			l->type = LIGHT_SPOT;
		}
		i++;
	}
	if (l->type == LIGHT_SPOT && l->angle == 0.0f)
		l->angle = 30.0f;
}

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
		l.type = LIGHT_POINT;
		parse_specs(&l, args);
		add_light(sc, l);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
