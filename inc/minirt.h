#ifndef __MINI_RT__
# define __MINI_RT__

# define WIDTH	2048.0f
# define HEIGHT	1152.0f
# define ASPECT_RATIO WIDTH / HEIGHT

# define ERROR_MSG_DFL "Error\n"

# include "entities.h"
# include "gc.h"
# include "mlx_interface.h"

typedef struct s_scene
{
	t_ambient_light		ambient;
	t_camera			cam;
	t_light				*lights;
	t_entity			*ents;
	size_t				light_count;
	size_t				ent_count;
	mlx					mlx;
	char				**av;
}						t_scene;

#endif
