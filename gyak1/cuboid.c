#include "cuboid.h"

#include <math.h>

void set_cuboid_size(Cuboid *cuboid, double x, double y, double z)
{
	cuboid->x = x;
	cuboid->y = y;
	cuboid->z = z;
}

double calc_cuboid_surface(const Cuboid *cuboid)
{
	double area = 2 * (cuboid->x * cuboid->y + cuboid->x * cuboid->z + cuboid->y * cuboid->z);
	return area;
}

double calc_cuboid_volume(const Cuboid *cuboid)
{
	double volume = cuboid->x * cuboid->y * cuboid->z;
	return volume;
}

int exam_cuboid_cube_surface(const Cuboid *cuboid)
{
	if (cuboid->x == cuboid->y || cuboid->x == cuboid->z || cuboid->y == cuboid->z)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
