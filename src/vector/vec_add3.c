/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_add3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:27:08 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:27:09 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vec_add3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	t_vec3	result;

	result.x = a.x + b.x + c.x;
	result.y = a.y + b.y + c.y;
	result.z = a.z + b.z + c.z;
	return (result);
}
