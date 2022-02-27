#include "cuboid.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
	Cuboid cuboid;
	double surface, volume;

	set_cuboid_size(&cuboid, 1, 4, 2);
	surface = calc_cuboid_surface(&cuboid);
	volume = calc_cuboid_volume(&cuboid);

	printf("Cuboid surface: %lf\nCuboid volume: %lf\n", surface, volume);
	if (exam_cuboid_cube_surface(&cuboid) == 1)
	{
		printf("It has a cube shaped surface!\n");
	}
	else
	{
		printf("It doesn't have a cube shaped surface!\n");
	}

	return 0;
}
