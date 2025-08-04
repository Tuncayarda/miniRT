/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:59:51 by tuaydin           #+#    #+#             */
/*   Updated: 2025/08/05 00:07:09 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>
# include <stdbool.h>

typedef struct			s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}						t_gc_node;

typedef struct			s_gc
{
	t_gc_node			*head;
}						gc;

void					*gc_track(gc *gc, void *ptr);
void					**gc_track_array(gc *gc, void **array);
void					gc_free_all(gc *gc);

#endif