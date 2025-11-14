/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:23:32 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:23:33 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"
#include "minirt.h"
#include "libft.h"
#include "gc.h"

void	add_light(t_scene *sc, t_light l)
{
	size_t	n;
	t_light	*new_lights;

	n = sc->light_count + 1;
	new_lights = gc_manager(malloc(sizeof(t_light) * n), MODE_ADD);
	if (!new_lights)
		return ;
	if (sc->lights)
		ft_memcpy(new_lights, sc->lights, sizeof(t_light) * sc->light_count);
	new_lights[n - 1] = l;
	sc->lights = new_lights;
	sc->light_count = n;
}
