/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_entity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:23:30 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:23:31 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

void	add_entity(t_scene *sc, void *ent, t_ent_type type)
{
	size_t		n;
	t_entity	*new_ents;

	n = sc->ent_count + 1;
	new_ents = gc_manager(malloc(sizeof(t_entity) * n), MODE_ADD);
	if (!new_ents)
		return ;
	if (sc->ents)
		ft_memcpy(new_ents, sc->ents, sizeof(t_entity) * sc->ent_count);
	new_ents[n - 1].ent = ent;
	new_ents[n - 1].type = type;
	sc->ents = new_ents;
	sc->ent_count = n;
}
