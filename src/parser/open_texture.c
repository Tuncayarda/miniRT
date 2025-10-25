#include "parser.h"
#include "entities.h"
#include "minirt.h"
#include "libft.h"
#include "util.h"

bool	open_texture(t_scene *sc, t_material *mat)
{
	mat->texture_img = mlx_xpm_file_to_image(
		sc->mlx.ptr,
		mat->texture_path,
		&mat->tex_width,
		&mat->tex_height
	);
	if (!mat->texture_img)
		return (false);
	mat->tex_addr = mlx_get_data_addr(
		mat->texture_img,
		&mat->tex_bpp,
		&mat->tex_line_len,
		&mat->tex_endian
	);
	if (!mat->tex_addr)
		return (false);
	return (true);
}
