#ifndef __PARSER_H__
# define __PARSER_H__

#include "minirt.h"

void	parser(scene *sc, int ac, char **av);

void	parse_amb_light(scene *sc, char **args);
void	parse_cam(scene *sc, char **args);
void	parse_light(scene *sc, char **args);
void	parse_sphere(scene *sc, char **args);
void	parse_plane(scene *sc, char **args);
void	parse_cylinder(scene *sc, char **args);

void	parse_material(material *mat, char **args);

#endif
