#include "entities.h"
#include "gc.h"
#include "libft.h"

void	parse_material(material *mat, char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "spc:", 4) == 0)
		{
			mat->has_spc = true;
			mat->specular_strength = ft_atof(args[i] + 4);
			mat->shininess = ft_atof(ft_strchr(args[i] + 4, ',') + 1);
		}
		else if (ft_strncmp(args[i], "che:", 4) == 0)
		{
			mat->has_checker = true;
			mat->checker_scale = ft_atof(ft_strrchr(args[i], ':') + 1);
			mat->checker_color.r = ft_atof(args[i] + 4);
			mat->checker_color.g = ft_atoi(ft_strchr(args[i] + 4, ',') + 1);
			mat->checker_color.b = ft_atoi(ft_strrchr(args[i], ',') + 1);
		}
		else if (ft_strncmp(args[i], "tex:", 4) == 0)
		{
			mat->has_texture = true;
			mat->texture_path = gc_manager(ft_substr(args[i], 4, ft_strlen(args[i] + 4) - ft_strlen(ft_strrchr(args[i], ','))) , MODE_ADD);
			mat->texture_scale = ft_atof(ft_strrchr(args[i], ',') + 1);
		}
		else if (ft_strncmp(args[i], "bum:", 4) == 0)
		{
			mat->has_bump= true;
			mat->bump_path = gc_manager(ft_substr(args[i], 4, ft_strlen(args[i] + 4) - ft_strlen(ft_strrchr(args[i], ','))) , MODE_ADD);
			mat->bump_strength = ft_atof(ft_strrchr(args[i], ',') + 1);
		}
		i++;
	}
}