/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_modul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:22:41 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:22:42 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color	color_modul(t_color a, t_color b)
{
	t_color	rtn;

	rtn.r = (a.r * b.r) / 255;
	rtn.g = (a.g * b.g) / 255;
	rtn.b = (a.b * b.b) / 255;
	return (rtn);
}
