#include "../headers/cub3d.h"

float calc_dist_to_screen(void)
{
	return((WIN_WIDTH / 2) / (tan(FOV / 2)));
}
