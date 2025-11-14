/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:24:23 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:49:25 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"
#include "gc.h"
#include "libft.h"

static void	parse_spc(t_material *mat, char **args, size_t i)
{
	mat->has_spc = true;
	mat->specular_strength = ft_atof(args[i] + 4);
	mat->shininess = ft_atof(ft_strchr(args[i] + 4, ',') + 1);
}

static void	parse_che(t_material *mat, char **args, size_t i)
{
	mat->has_checker = true;
	mat->checker_scale = ft_atof(ft_strrchr(args[i], ':') + 1);
	mat->checker_color.r = ft_atoi(ft_strchr(args[i] + 4, ',') + 1);
	mat->checker_color.g = ft_atoi(
			ft_strchr(ft_strchr(args[i] + 4, ',') + 1, ',') + 1);
	mat->checker_color.b = ft_atoi(ft_strrchr(args[i], ',') + 1);
}

static void	parse_tex(t_material *mat, char **args, size_t i)
{
	mat->has_texture = true;
	mat->texture_path = gc_manager(ft_substr(args[i],
				4, ft_strlen(args[i] + 4)
				- ft_strlen(ft_strrchr(args[i], ','))), MODE_ADD);
}

static void	parse_bum(t_material *mat, char **args, size_t i)
{
	mat->has_bump = true;
	mat->bump_strength = ft_atof(ft_strchr(args[i], ':') + 1);
}

void	parse_material(t_material *mat, char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "spc:", 4) == 0)
			parse_spc(mat, args, i);
		else if (ft_strncmp(args[i], "che:", 4) == 0)
			parse_che(mat, args, i);
		else if (ft_strncmp(args[i], "tex:", 4) == 0)
			parse_tex(mat, args, i);
		else if (ft_strncmp(args[i], "bum:", 4) == 0)
			parse_bum(mat, args, i);
		i++;
	}
}
