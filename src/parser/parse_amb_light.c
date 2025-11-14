/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amb_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:24:05 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:24:06 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "util.h"

void	parse_amb_light(t_scene *sc, char **args)
{
	if (args && args[0] && args[1] && args[2])
	{
		sc->ambient.ratio = ft_atof(args[1]);
		sc->ambient.color.r = ft_atoi(args[2]);
		sc->ambient.color.g = ft_atoi(ft_strchr(args[2], ',') + 1);
		sc->ambient.color.b = ft_atoi(ft_strrchr(args[2], ',') + 1);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
