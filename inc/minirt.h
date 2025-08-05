#ifndef __MINI_RT__
# define __MINI_RT__

# define WIDTH	1920
# define HEIGHT	1080

# define ERROR_MSG_DFL "Error\n"

# include "entities.h"
# include "gc.h"

typedef struct	s_scene
{
	ambient_light	ambient;
	camera			cam;
	light			*lights;
	entity			*ents;
	size_t			light_count;
	size_t			ent_count;
}				scene;

#endif
