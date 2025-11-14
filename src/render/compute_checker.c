/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:24:41 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:47:49 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"

static t_color	get_checker_color(t_trace_var *var)
{
	if (var->type == ENT_CIRCLE)
	{
		var->iu = (int)floorf(var->u * var->mat.checker_scale);
		if ((var->iu & 1) == 0)
			return (var->mat.checker_color);
		else
			return (var->base);
	}
	else
	{
		var->iu = (int)floorf(var->u * var->mat.checker_scale);
		var->iv = (int)floorf(var->v * var->mat.checker_scale);
		if (((var->iu + var->iv) & 1) == 0)
			return (var->mat.checker_color);
		else
			return (var->base);
	}
}

void	compute_checker(t_scene *sc, t_trace_var *var)
{
	(void)sc;
	if (var->mat.has_checker)
	{
		compute_uv(sc, var);
		var->base = get_checker_color(var);
	}
}
