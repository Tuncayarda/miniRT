#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"

void	parser(t_scene *sc, int ac, char **av);

void	parse_amb_light(t_scene *sc, char **args);
void	parse_cam(t_scene *sc, char **args);
void	parse_light(t_scene *sc, char **args);
void	parse_sphere(t_scene *sc, char **args);
void	parse_plane(t_scene *sc, char **args);
void	parse_cylinder(t_scene *sc, char **args);
bool	open_texture(t_scene *sc, t_material *mat);
void	parse_material(t_material *mat, char **args);

#endif
