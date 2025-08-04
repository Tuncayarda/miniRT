#include <mlx.h>
#include "minirt.h"
#include "parser.h"

#include <stdio.h>

int main(int ac, char **av)
{
    scene	sc;
	sc.gc.head = NULL;
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
		sc.cam.loc.x, sc.cam.loc.y, sc.cam.loc.z);
	printf("  Direction: %.2f, %.2f, %.2f\n",
		sc.cam.dir.x, sc.cam.dir.y, sc.cam.dir.z);
	printf("  FOV: %d\n", sc.cam.fov);

	for (size_t i = 0; i < sc.light_count; i++)
	printf("\nLight %zu:\n  Position: %.2f, %.2f, %.2f\n  Ratio: %.2f\n  Color (R,G,B): %u, %u, %u\n",
		i,
		sc.lights[i].loc.x, sc.lights[i].loc.y, sc.lights[i].loc.z,
		sc.lights[i].ratio,
		sc.lights[i].color.r, sc.lights[i].color.g, sc.lights[i].color.b);
	gc_free_all(&sc.gc);
	return (0);
}