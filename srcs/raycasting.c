#include "../headers/cub3d.h"

float	calc_step_x(t_vector ray_direction, float x_component)
{
	float	step;

	if (ray_direction.x != 0)
		step = x_component * sqrt(1 + (ray_direction.y * ray_direction.y) / (ray_direction.x * ray_direction.x));
	else
		step = FLT_MAX;
	return (step);
}

float	calc_step_y(t_vector ray_direction, float y_component)
{
	float	step;

	if (ray_direction.y != 0)
		step = y_component * sqrt(1 + (ray_direction.x * ray_direction.x) / (ray_direction.y * ray_direction.y));
	else
		step = FLT_MAX;
	return (step);
}

float	distance_to_x_axis(t_vector position, t_vector direction)
{
	float	offset;
	float	first_step;

	if (direction.y == 0)
		return (FLT_MAX);
	else if (direction.y < 0)
		offset = position.y - (int)position.y;
	else
		offset = (int)position.y + 1 - position.y;
	first_step = calc_step_y(direction, offset);
	return (first_step);
}

float	distance_to_y_axis(t_vector position, t_vector direction)
{
	float	offset;
	float	first_step;

	if (direction.x == 0)
		return (FLT_MAX);
	else if (direction.x < 0)
		offset = position.x - (int)position.x;
	else
		offset = (int)position.x + 1 - position.x;
	first_step = calc_step_x(direction, offset);
	return (first_step);
}

void	cast_ray(t_ray ray[WIN_WIDTH], t_player player)
{
	int	i;
	float	fov;
	float	app;

	i = 0;
	fov = (FOV * M_PI) / 180;
	app = fov / WIN_WIDTH;
	while (i < WIN_WIDTH)
	{
		if (i == 0)
			ray[i].direction = rotate_vector(player.direction, -(fov / 2));
		else if (i != WIN_WIDTH / 2)
			ray[i].direction = rotate_vector(ray[i - 1].direction, app);
		else
			ray[i].direction = player.direction;
		ray[i].step_x = calc_step_x(ray[i].direction, 1);
		ray[i].step_y = calc_step_y(ray[i].direction, 1);
		ray[i].distance = 0;
		i++;
	}
}
