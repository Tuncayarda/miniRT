/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:22:39 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:22:40 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color.h"

t_color	color_add(t_color a, t_color b)
{
	t_color	rtn;

	rtn.r = fminf(255, a.r + b.r);
	rtn.g = fminf(255, a.g + b.g);
	rtn.b = fminf(255, a.b + b.b);
	return (rtn);
}
