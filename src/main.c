#include <mlx.h>
#include "minirt.h"
#include "parser.h"

#include <stdio.h>

int main(int ac, char **av)
{
    scene   sc;
	sc.gc.head = NULL;
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

	gc_free_all(&sc.gc);
	return (0);
}