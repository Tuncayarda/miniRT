/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_entity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:23:37 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:23:38 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entities.h"
#include "gc.h"
#include "libft.h"

void	*generate_entity(void *src, t_ent_type type)
{
	size_t	size;
	void	*ret;

	if (type == ENT_SPHERE)
		size = sizeof(t_sphere);
	else if (type == ENT_PLANE)
		size = sizeof(t_plane);
	else if (type == ENT_CYLINDER)
		size = sizeof(t_cylinder);
	else if (type == ENT_CIRCLE)
		size = sizeof(t_circle);
	else
		return (NULL);
	ret = gc_manager(malloc(size), MODE_ADD);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, src, size);
	return (ret);
}
