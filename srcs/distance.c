#include "../headers/cub3d.h"

float	calc_dist_to_screen(void)
{
<<<<<<< Updated upstream
	return (WIN_WIDTH / tan(FOV));
}

float	calc_projected_wall_height(float distance_to_wall)
{
	float	distance_to_screen;
	float	real_wall_height;
	float	projected_wall_height;
	float	distorted_wall_height;

	distance_to_screen = calc_dist_to_screen();
	real_wall_height = WIN_HEIGHT / 2;
	distorted_wall_height = (distance_to_screen / distance_to_wall) * real_wall_height;
	projected_wall_height = distorted_wall_height * cos(FOV / 2);
	return (projected_wall_height);
=======
	return ((WIN_WIDTH / 2) / (tan (FOV / 2)));
>>>>>>> Stashed changes
}
