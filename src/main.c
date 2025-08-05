#include <mlx.h>
#include "minirt.h"
#include "parser.h"

#include <stdio.h>

#include "libft.h"
#include "gc.h"

int main(int ac, char **av)
{
    scene	sc;
	sc.light_count = 0;
	sc.ent_count = 0;
	sc.lights = NULL;

    parser(&sc, ac, av);

    printf("Ambient Light:\n");
	printf("  Ratio: %.2f\n", sc.ambient.ratio);
	printf("  Color (R,G,B): %u, %u, %u\n",
		sc.ambient.color.r,
		sc.ambient.color.g,
		sc.ambient.color.b);

	printf("\nCamera Info:\n");
	printf("  Position: %.2f, %.2f, %.2f\n",
		sc.cam.pos.x, sc.cam.pos.y, sc.cam.pos.z);
	printf("  Direction: %.2f, %.2f, %.2f\n",
		sc.cam.dir.x, sc.cam.dir.y, sc.cam.dir.z);
	printf("  FOV: %d\n", sc.cam.fov);

	for (size_t i = 0; i < sc.light_count; i++)
	{
		printf("\nLight %zu:\n  Position: %.2f, %.2f, %.2f\n  Ratio: %.2f\n  Color (R,G,B): %u, %u, %u\n",
			i,
			sc.lights[i].pos.x, sc.lights[i].pos.y, sc.lights[i].pos.z,
			sc.lights[i].ratio,
			sc.lights[i].color.r, sc.lights[i].color.g, sc.lights[i].color.b);
		if (sc.lights[i].type == LIGHT_SPOT)
		{
			printf("  Type: SPOT\n");
			printf("  Direction: %.2f, %.2f, %.2f\n",
				sc.lights[i].dir.x, sc.lights[i].dir.y, sc.lights[i].dir.z);
			printf("  Angle: %.2f\n", sc.lights[i].angle);
		}
		else
		{
			printf("  Type: POINT\n");
		}
	}

	printf("\nEntities (%zu total):\n", sc.ent_count);
	for (size_t i = 0; i < sc.ent_count; i++)
	{
		printf("\n  Entity %zu: ", i);
		if (sc.ents[i].type == ENT_SPHERE)
		{
			printf("SPHERE\n");
			sphere *s = (sphere *)sc.ents[i].ent;
			printf("    Position: %.2f, %.2f, %.2f\n", s->pos.x, s->pos.y, s->pos.z);
			printf("    Diameter: %.2f\n", s->dia);
			printf("    Color (R,G,B): %u, %u, %u\n",
				s->color.r, s->color.g, s->color.b);
			printf("    Specular: strength=%.2f, shininess=%.2f\n",
				s->mat.specular_strength, s->mat.shininess);
			if (s->mat.has_checker)
				printf("    Checker: scale=%.2f, color (R,G,B) = %u, %u, %u\n",
					s->mat.checker_scale,
					s->mat.checker_color.r, s->mat.checker_color.g, s->mat.checker_color.b);
		}
		else if (sc.ents[i].type == ENT_PLANE)
			printf("PLANE\n");
		else if (sc.ents[i].type == ENT_CYLINDER)
			printf("CYLINDER\n");
		else
			printf("UNKNOWN\n");
	}

	gc_manager(NULL, MODE_FREE);

	return (0);
}