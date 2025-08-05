#include "parser.h"
#include "entities.h"
#include "minirt.h"
#include "libft.h"
#include "util.h"

static void	parse_specs(sphere *s, char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "spc:", 4) == 0)
		{
			s->mat.has_spc = true;
			s->mat.specular_strength = ft_atof(args[i] + 4);
			s->mat.shininess = ft_atof(ft_strchr(args[i] + 4, ',') + 1);
		}
		else if (ft_strncmp(args[i], "che:", 4) == 0)
		{
			s->mat.has_checker = true;
			s->mat.checker_scale = ft_atof(ft_strrchr(args[i], ':') + 1);
			s->mat.checker_color.r = ft_atof(args[i] + 4);
			s->mat.checker_color.g = ft_atoi(ft_strchr(args[i] + 4, ',') + 1);
			s->mat.checker_color.b = ft_atoi(ft_strrchr(args[i], ',') + 1);
		}
		else if (ft_strncmp(args[i], "tex:", 4) == 0)
		{
			s->mat.has_texture = true;
		
		}
		else if (ft_strncmp(args[i], "bum:", 4) == 0)
		{

		}
		i++;
	}
}

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
		parse_specs(&s, args);
		//some function to generate this entity
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
