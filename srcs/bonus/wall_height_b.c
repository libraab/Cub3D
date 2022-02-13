#include "../../headers/cub3d.h"

float	calc_dist_to_screen(void)
{
	float	fov;

	fov = (FOV * M_PI) / 180;
	return (WIN_WIDTH / tan(fov));
}

float	calc_wall_height(float distance_to_wall, float angle)
{
	float	distance_to_screen;
	float	real_wall_height;
	float	projected_wall_height;
	float	distorted_wall_height;

	distance_to_screen = calc_dist_to_screen();
	real_wall_height = WIN_HEIGHT / 6;
	distorted_wall_height = ((distance_to_screen / TILE_SIZE)
			/ distance_to_wall) * real_wall_height;
	projected_wall_height = distorted_wall_height / cos(angle);
	return (projected_wall_height);
}

float	get_wall_height(float distance, int ray_number)
{
	float	fov;
	float	angle_per_pixel;
	float	wall_height;

	fov = (FOV * M_PI) / 180;
	angle_per_pixel = fov / WIN_WIDTH;
	if (ray_number < WIN_WIDTH / 2)
		wall_height = calc_wall_height(distance, \
				((fov / 2) - (ray_number * angle_per_pixel)));
	else
		wall_height = calc_wall_height(distance, \
				((ray_number - WIN_WIDTH / 2) * angle_per_pixel));
	return (wall_height);
}
