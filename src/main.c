#include <mlx.h>
#include "minirt.h"
#include "parser.h"

#include <stdio.h>

#include "libft.h"
#include "gc.h"

int main(int ac, char **av)
{
    scene	sc;
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
	//gc_manager(NULL, MODE_FREE);

	return (0);
}