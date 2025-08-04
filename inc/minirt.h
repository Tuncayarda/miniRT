#ifndef __MINI_RT__
# define __MINI_RT__

#include "entities.h"

typedef struct	s_scene
{
	ambient_light	ambient;
	camera			cam;
	light			*lights;
	entity			*ents;
	size_t			ent_count;
}				scene;



#endif
