#include "parser.h"
#include "entities.h"
#include "minirt.h"
#include "libft.h"
#include "util.h"

bool    open_skybox(t_scene *sc)
{
    sc->sky.texture_img = mlx_xpm_file_to_image(
        sc->mlx.ptr,
        sc->sky.texture_path,
        &sc->sky.tex_width,
        &sc->sky.tex_height
    );
    if (!sc->sky.texture_img)
        return (false);
    sc->sky.tex_addr = mlx_get_data_addr(
        sc->sky.texture_img,
        &sc->sky.tex_bpp,
        &sc->sky.tex_line_len,
        &sc->sky.tex_endian
    );
    if (!sc->sky.tex_addr)
        return (false);
    return (true);
}


void	parse_skybox(t_scene *sc, char **args)
{
    sc->sky.has_skybox = true;

    if (ft_strncmp(args[1], "tex:", 4) == 0)
    {
        sc->sky.texture_path = gc_manager(ft_substr(args[1],
				4, ft_strlen(args[1] + 4)
				- ft_strlen(ft_strrchr(args[1], ','))), MODE_ADD);
    }
    open_skybox(sc);
}
