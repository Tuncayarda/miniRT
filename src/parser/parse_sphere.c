/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:24:30 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:24:31 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "entities.h"
#include "minirt.h"
#include "libft.h"
#include "util.h"

void	parse_sphere(t_scene *sc, char **args)
{
	t_sphere	s;

	ft_memset(&s, 0, sizeof(t_sphere));
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
		if (s.mat.has_texture && !open_texture(sc, &s.mat))
			raise_error(sc, "sphere: texture open failed");
		add_entity(sc, generate_entity(&s, ENT_SPHERE), ENT_SPHERE);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
