/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:24:25 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:24:26 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "entities.h"
#include "util.h"
#include "libft.h"
#include "parser.h"

void	parse_plane(t_scene *sc, char **args)
{
	t_plane	p;

	ft_memset(&p, 0, sizeof(t_plane));
	if (args && args[0] && args[1] && args[2] && args[3])
	{
		p.pos.x = ft_atof(args[1]);
		p.pos.y = ft_atof(ft_strchr(args[1], ',') + 1);
		p.pos.z = ft_atof(ft_strrchr(args[1], ',') + 1);
		p.axis.x = ft_atof(args[2]);
		p.axis.y = ft_atof(ft_strchr(args[2], ',') + 1);
		p.axis.z = ft_atof(ft_strrchr(args[2], ',') + 1);
		p.color.r = ft_atof(args[3]);
		p.color.g = ft_atof(ft_strchr(args[3], ',') + 1);
		p.color.b = ft_atof(ft_strrchr(args[3], ',') + 1);
		parse_material(&p.mat, args);
		if (p.mat.has_texture && !open_texture(sc, &p.mat))
			raise_error(sc, "plane: texture open failed");
		add_entity(sc, generate_entity(&p, ENT_PLANE), ENT_PLANE);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
