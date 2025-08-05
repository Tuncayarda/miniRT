#include "parser.h"
#include "util.h"
#include "get_next_line.h"
#include "libft.h"
#include "gc.h"
#include <fcntl.h>

void	parse_line(scene *sc, char *line)
{
	char **args;

	if (!line || *line == '\n')
		return ;
	args = gc_manager(ft_split(line, '\t'), MODE_ADD_ARR);
	if (!args || !args[0])
		return ;
	if (ft_strcmp(args[0], "A") == 0)
		parse_amb_light(sc, args);
	else if (ft_strcmp(args[0], "C") == 0)
		parse_cam(sc, args);
	else if (ft_strcmp(args[0], "L") == 0)
		parse_light(sc, args);
	else if (ft_strcmp(args[0], "sp") == 0)
		parse_sphere(sc, args);
}

void	parse(scene *sc, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		parse_line(sc, line);
		free(line);
		line = get_next_line(fd);
	}
}

void	parser(scene *sc, int ac, char **av)
{
	int	fd;

	if (ac == 2 && av && av[1])
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			raise_error(sc, ERROR_MSG_DFL);
		parse(sc, fd);
	}
	else
		raise_error(sc, ERROR_MSG_DFL);
}
