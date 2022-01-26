#include "../headers/cub3d.h"

float	calc_step_x(t_vector ray_direction)
{
	float	step;

	step = sqrt(1 + (ray_direction.y * ray_direction.y) / (ray_direction.x * ray_direction.x));
	return (step);
}

float	calc_step_y(t_vector ray_direction)
{
	float	step;

	step = sqrt(1 + (ray_direction.x * ray_direction.x) / (ray_direction.y * ray_direction.y));
	return (step);
}

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

void	cast_rays(t_ray rays[WIN_WIDTH], t_vector player_direction)
{
	int	i;

	rays[0].direction = rotate_vector(player_direction, -(FOV / 2));
	i = 1;
	while (i < WIN_WIDTH)
	{
		rays[i].direction = rotate_vector(rays[i - 1].direction, ANGLE_PER_PIXEL);
		rays[i].step_x = calc_step_x(rays[i].direction);
		rays[i].step_y = calc_step_y(rays[i].direction);
		i++;
	}
}
