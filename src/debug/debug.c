#include "minirt.h"
#include <stdio.h>

void	print_scene_debug(t_scene *sc)
{
	printf("Ambient Light:\n");
	printf("  Ratio: %.2f\n", sc->ambient.ratio);
	printf("  Color (R,G,B): %u, %u, %u\n",
		sc->ambient.color.r,
		sc->ambient.color.g,
		sc->ambient.color.b);

	printf("\nCamera Info:\n");
	printf("  Position: %.2f, %.2f, %.2f\n",
		sc->cam.pos.x, sc->cam.pos.y, sc->cam.pos.z);
	printf("  Direction: %.2f, %.2f, %.2f\n",
		sc->cam.dir.x, sc->cam.dir.y, sc->cam.dir.z);
	printf("  FOV: %d\n", sc->cam.fov);

	for (size_t i = 0; i < sc->light_count; i++)
	{
		printf("\nLight %zu:\n  Position: %.2f, %.2f, %.2f\n  Ratio: %.2f\n  Color (R,G,B): %u, %u, %u\n",
			i,
			sc->lights[i].pos.x, sc->lights[i].pos.y, sc->lights[i].pos.z,
			sc->lights[i].ratio,
			sc->lights[i].color.r, sc->lights[i].color.g, sc->lights[i].color.b);
			printf("  Type: POINT\n");
	}

	printf("\nEntities (%zu total):\n", sc->ent_count);
	for (size_t i = 0; i < sc->ent_count; i++)
	{
		printf("\n  Entity %zu: ", i);
		if (sc->ents[i].type == ENT_SPHERE)
		{
			printf("SPHERE\n");
			t_sphere *s = (t_sphere *)sc->ents[i].ent;
			printf("    Position: %.2f, %.2f, %.2f\n", s->pos.x, s->pos.y, s->pos.z);
			printf("    Diameter: %.2f\n", s->dia);
			printf("    Color (R,G,B): %u, %u, %u\n", s->color.r, s->color.g, s->color.b);
			printf("    Specular: strength=%.2f, shininess=%.2f\n",
				s->mat.specular_strength, s->mat.shininess);
			if (s->mat.has_checker)
				printf("    Checker: scale=%.2f, color (R,G,B) = %u, %u, %u\n",
					s->mat.checker_scale,
					s->mat.checker_color.r, s->mat.checker_color.g, s->mat.checker_color.b);
			if (s->mat.has_texture)
				printf("    Texture: path=%s\n",
					s->mat.texture_path ? s->mat.texture_path : "(null)");
			if (s->mat.has_bump)
				printf("    Bump Map: path=%s, strength=%.2f\n",
					s->mat.bump_path ? s->mat.bump_path : "(null)",
					s->mat.bump_strength);
		}
		else if (sc->ents[i].type == ENT_PLANE)
		{
			printf("PLANE\n");
			t_plane *p = (t_plane *)sc->ents[i].ent;
			printf("    Position: %.2f, %.2f, %.2f\n", p->pos.x, p->pos.y, p->pos.z);
			printf("    Axis: %.2f, %.2f, %.2f\n", p->axis.x, p->axis.y, p->axis.z);
			printf("    Color (R,G,B): %u, %u, %u\n", p->color.r, p->color.g, p->color.b);
			printf("    Specular: strength=%.2f, shininess=%.2f\n",
				p->mat.specular_strength, p->mat.shininess);
			if (p->mat.has_checker)
				printf("    Checker: scale=%.2f, color (R,G,B) = %u, %u, %u\n",
					p->mat.checker_scale,
					p->mat.checker_color.r, p->mat.checker_color.g, p->mat.checker_color.b);
			if (p->mat.has_texture)
				printf("    Texture: path=%s\n",
					p->mat.texture_path ? p->mat.texture_path : "(null)");
			if (p->mat.has_bump)
				printf("    Bump Map: path=%s, strength=%.2f\n",
					p->mat.bump_path ? p->mat.bump_path : "(null)",
					p->mat.bump_strength);
		}
		else if (sc->ents[i].type == ENT_CYLINDER)
		{
			printf("CYLINDER\n");
			t_cylinder *c = (t_cylinder *)sc->ents[i].ent;
			printf("    Position: %.2f, %.2f, %.2f\n", c->pos.x, c->pos.y, c->pos.z);
			printf("    Axis: %.2f, %.2f, %.2f\n", c->axis.x, c->axis.y, c->axis.z);
			printf("    Diameter: %.2f\n", c->dia);
			printf("    Height: %.2f\n", c->h);
			printf("    Color (R,G,B): %u, %u, %u\n", c->color.r, c->color.g, c->color.b);
			printf("    Specular: strength=%.2f, shininess=%.2f\n",
				c->mat.specular_strength, c->mat.shininess);
			if (c->mat.has_checker)
				printf("    Checker: scale=%.2f, color (R,G,B) = %u, %u, %u\n",
					c->mat.checker_scale,
					c->mat.checker_color.r, c->mat.checker_color.g, c->mat.checker_color.b);
			if (c->mat.has_texture)
				printf("    Texture: path=%s\n",
					c->mat.texture_path ? c->mat.texture_path : "(null)");
			if (c->mat.has_bump)
				printf("    Bump Map: path=%s, strength=%.2f\n",
					c->mat.bump_path ? c->mat.bump_path : "(null)",
					c->mat.bump_strength);
		}
		else if (sc->ents[i].type == ENT_CIRCLE)
		{
			printf("CIRCLE\n");
			t_circle *ci = (t_circle *)sc->ents[i].ent;
			printf("    Position: %.2f, %.2f, %.2f\n", ci->pos.x, ci->pos.y, ci->pos.z);
			printf("    Axis: %.2f, %.2f, %.2f\n", ci->axis.x, ci->axis.y, ci->axis.z);
			printf("    Radius: %.2f\n", ci->radius);
			printf("    Specular: strength=%.2f, shininess=%.2f\n",
				ci->mat.specular_strength, ci->mat.shininess);
			if (ci->mat.has_checker)
				printf("    Checker: scale=%.2f, color (R,G,B) = %u, %u, %u\n",
					ci->mat.checker_scale,
					ci->mat.checker_color.r, ci->mat.checker_color.g, ci->mat.checker_color.b);
			if (ci->mat.has_texture)
				printf("    Texture: path=%s\n",
					ci->mat.texture_path ? ci->mat.texture_path : "(null)");
			if (ci->mat.has_bump)
				printf("    Bump Map: path=%s, strength=%.2f\n",
					ci->mat.bump_path ? ci->mat.bump_path : "(null)",
					ci->mat.bump_strength);
		}
		else
			printf("UNKNOWN\n");
	}
}
