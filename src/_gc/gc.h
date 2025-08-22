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

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}						t_gc_node;

void	*gc_manager(void *ptr, t_gc_mode mode);

#endif