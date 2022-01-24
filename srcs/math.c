#include "../headers/cub3d.h"

t_vector	starting_direction(char player_character)
{
	t_vector	direction;

	direction.x = 0;
	direction.y = 0;
	if (player_character == 'N')
	{
		direction.x = 0;
		direction.y = -1;
	}
	else if (player_character == 'E')
	{
		direction.x = 1;
		direction.y = 0;
	}
	else if (player_character == 'S')
	{
		direction.x = 0;
		direction.y = 1;
	}
	else if (player_character == 'W')
	{
		direction.x = -1;
		direction.y = 0;
	}
	return (direction);
}

t_vector	rotate_vector(t_vector to_rotate, float angle)
{
	t_vector	rotated;

	rotated.x = to_rotate.x * cos(angle) - to_rotate.y * sin(angle);
	rotated.y = to_rotate.x * sin(angle) + to_rotate.y * cos(angle);
	return (rotated);
}

t_vector	*cast_rays(t_vector direction)
{
	t_vector	*rays;
	int			i;

	rays = ft_calloc(WIN_WIDTH, sizeof(t_vector));
	rays[0] = rotate_vector(direction, -(FOV / 2));
	i = 1;
	while (i < WIN_WIDTH)
	{
		rays[i] = rotate_vector(rays[i - 1], ANGLE_PER_PIXEL);
		i++;
	}
	return (rays);
}
