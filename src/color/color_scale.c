/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:22:43 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:22:44 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color	color_scale(t_color clr, float intensity)
{
	t_color	rtn;

	rtn.r = clr.r * intensity;
	rtn.g = clr.g * intensity;
	rtn.b = clr.b * intensity;
	return (rtn);
}
