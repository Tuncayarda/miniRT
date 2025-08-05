/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:59:51 by tuaydin           #+#    #+#             */
/*   Updated: 2025/08/05 05:28:20 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>
# include <stdbool.h>

typedef enum e_gc_mode
{
	MODE_ADD,
	MODE_ADD_ARR,
	MODE_FREE
}	t_gc_mode;

typedef struct			s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}						t_gc_node;

void	*gc_manager(void *ptr, t_gc_mode mode);

#endif