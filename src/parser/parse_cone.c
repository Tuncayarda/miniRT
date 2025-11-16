/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:38:31 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 22:24:29 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "entities.h"
#include "util.h"
#include "libft.h"
#include "parser.h"

void	parse_cone(t_scene *sc, char **args)
{
	t_cone	co;

	ft_memset(&co, 0, sizeof(t_cone));
	if (args && args[0] && args[1] && args[2] && args[3] && args[4] && args[5])
	{
		co.pos.x = ft_atof(args[1]);
		co.pos.y = ft_atof(ft_strchr(args[1], ',') + 1);
		co.pos.z = ft_atof(ft_strrchr(args[1], ',') + 1);
		co.axis.x = ft_atof(args[2]);
		co.axis.y = ft_atof(ft_strchr(args[2], ',') + 1);
		co.axis.z = ft_atof(ft_strrchr(args[2], ',') + 1);
		co.angle = ft_atof(args[3]);
		co.h = ft_atof(args[4]);
		co.color.r = ft_atof(args[5]);
		co.color.g = ft_atof(ft_strchr(args[5], ',') + 1);
		co.color.b = ft_atof(ft_strrchr(args[5], ',') + 1);
		parse_material(&co.mat, args);
		if (co.mat.has_texture && !open_texture(sc, &co.mat))
			raise_error(sc, "cone: texture open failed");
		add_entity(sc, generate_entity(&co, ENT_CONE), ENT_CONE);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
