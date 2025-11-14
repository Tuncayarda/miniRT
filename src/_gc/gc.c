/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:22:25 by tuaydin           #+#    #+#             */
/*   Updated: 2025/11/14 18:22:26 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

static t_gc_node	**get_gc_head(void)
{
	static t_gc_node	*head;

	return (&head);
}

static void	gc_free_all(void)
{
	t_gc_node	**head;
	t_gc_node	*tmp;

	head = get_gc_head();
	while (*head)
	{
		if ((*head)->ptr)
			free((*head)->ptr);
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

static void	*gc_track_array(void **arr)
{
	size_t	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		gc_manager(arr[i], MODE_ADD);
		i++;
	}
	gc_manager(arr, MODE_ADD);
	return (arr);
}

void	*gc_manager(void *ptr, t_gc_mode mode)
{
	t_gc_node	**head;
	t_gc_node	*node;

	head = get_gc_head();
	if (mode == MODE_FREE)
	{
		gc_free_all();
		return (NULL);
	}
	if (mode == MODE_ADD_ARR)
		return (gc_track_array((void **)ptr));
	if (!ptr)
		return (NULL);
	node = (t_gc_node *)malloc(sizeof(t_gc_node));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->next = *head;
	*head = node;
	return (ptr);
}
