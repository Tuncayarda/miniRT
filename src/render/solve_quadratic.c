/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:26:50 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:26:51 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"

bool	solve_quadratic(float a, float b, float c, float *t)
{
	float	discriminant;
	float	temp;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	temp = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (temp < 0)
		temp = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (temp < 0)
		return (false);
	*t = temp;
	return (true);
}
