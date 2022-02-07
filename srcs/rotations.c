#include "../headers/cub3d.h"

int	rotate_player(int keycode, t_data *cub)
{
	if (keycode == KEY_ARROW_LEFT)
		cub->player.direction = rotate_vector(cub->player.direction, -ROTATION_ANGLE);
	if (keycode == KEY_ARROW_RIGHT)
		cub->player.direction = rotate_vector(cub->player.direction, ROTATION_ANGLE);
	return (0);
}

t_direction	rotate_vector(t_direction to_rotate, float angle)
{
	t_direction	rotated;

	rotated.x = to_rotate.x * cos(angle) - to_rotate.y * sin(angle);
	rotated.y = to_rotate.x * sin(angle) + to_rotate.y * cos(angle);
	return (rotated);
}
