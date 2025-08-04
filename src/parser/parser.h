#ifndef __PARSER_H__
# define __PARSER_H__

#include "minirt.h"

void	parser(scene *sc, int ac, char **av);

void	set_amb_light(scene *sc, char **args);
void	set_cam(scene *sc, char **args);

#endif
