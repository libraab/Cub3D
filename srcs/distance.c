#include "../headers/cub3d.h"

float	calc_dist_to_screen(void)
{
	return (WIN_WIDTH / tan(FOV));
}

float	calc_projected_wall_height(float distance_to_wall, float angle)
{
	float	distance_to_screen;
	float	real_wall_height;
	float	projected_wall_height;
	float	distorted_wall_height;

	distance_to_screen = calc_dist_to_screen();
	real_wall_height = WIN_HEIGHT / 6;
	distorted_wall_height = ((distance_to_screen / TILE_SIZE) / distance_to_wall) * real_wall_height;
	projected_wall_height = distorted_wall_height / cos(angle); //wrong angle
	return (projected_wall_height);
}
