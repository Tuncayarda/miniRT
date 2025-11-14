/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:24:10 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:24:11 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "entities.h"
#include "util.h"
#include "libft.h"
#include "parser.h"

static void	generate_circles(t_scene *sc, t_cylinder *cy)
{
	t_circle	top;
	t_circle	bottom;

	ft_memset(&top, 0, sizeof(t_circle));
	ft_memset(&bottom, 0, sizeof(t_circle));
	if (cy)
	{
		top.axis = vec_norm(cy->axis);
		top.pos = vec_add(cy->pos, vec_scale(vec_norm(cy->axis), cy->h / 2));
		top.radius = cy->dia / 2;
		top.mat = cy->mat;
		top.color = cy->color;
		cy->top = top;
		add_entity(sc, generate_entity(&top, ENT_CIRCLE), ENT_CIRCLE);
		bottom.axis = vec_scale(vec_norm(cy->axis), -1.0f);
		bottom.pos = vec_sub(cy->pos, vec_scale(vec_norm(cy->axis), cy->h / 2));
		bottom.radius = cy->dia / 2;
		bottom.color = cy->color;
		bottom.mat = cy->mat;
		cy->bottom = bottom;
		add_entity(sc, generate_entity(&bottom, ENT_CIRCLE), ENT_CIRCLE);
	}
}

void	parse_cylinder(t_scene *sc, char **args)
{
	t_cylinder	c;

	ft_memset(&c, 0, sizeof(t_cylinder));
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
		if (c.mat.has_texture && !open_texture(sc, &c.mat))
			raise_error(sc, "cylinder: texture open failed");
		generate_circles(sc, &c);
		add_entity(sc, generate_entity(&c, ENT_CYLINDER), ENT_CYLINDER);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
