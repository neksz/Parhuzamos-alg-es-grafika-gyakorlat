#ifndef CUBOID_H
#define CUBOID_H

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct Cuboid
{
	double x;
	double y;
	double z;
} Cuboid;

/**
 * Set the data of the cuboid
 */
void set_cuboid_size(Cuboid *cuboid, double x, double y, double z);

/**
 * Calculate the surface of the cuboid.
 */
double calc_cuboid_surface(const Cuboid *cuboid);

/**
 * Calculate the volume of the cuboid.
 */
double calc_cuboid_volume(const Cuboid *cuboid);

/**
 * Examine cuboid, does it have a cube shaped surface?
 */
int exam_cuboid_cube_surface(const Cuboid *cuboid);

#endif // CUBOID_H
