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

float	distance_to_x_axis(int on_x, t_coordinates position, t_vector direction)
{
	float	offset;
	float	first_step;

	(void)on_x;
	if (position.x % TILE_SIZE == 0)
		offset = TILE_SIZE;
	else if (direction.y == 0)
		return (FLT_MAX);
	else if (direction.y < 0)
		offset = position.y % TILE_SIZE;
	else
		offset = TILE_SIZE - (position.y % TILE_SIZE);
	first_step = calc_step_y(direction, offset);
	return (first_step);
}

float	distance_to_y_axis(int on_y, t_coordinates position, t_vector direction)
{
	float	offset;
	float	first_step;

	(void)on_y;
	if (position.y % TILE_SIZE == 0)
		offset = TILE_SIZE;
	else if (direction.x == 0)
		return (FLT_MAX);
	else if (direction.x < 0)
		offset = position.x % TILE_SIZE;
	else
		offset = TILE_SIZE - (position.x % TILE_SIZE);
	first_step = calc_step_x(direction, offset);
	return (first_step);
}

void	cast_ray(t_ray ray[WIN_WIDTH], t_player player)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		if (i == 0)
			ray[i].direction = rotate_vector(player.direction, -(FOV / 2));
		else if (i != WIN_WIDTH / 2)
			ray[i].direction = rotate_vector(ray[i - 1].direction, ANGLE_PER_PIXEL);
		else
			ray[i].direction = player.direction;
		ray[i].current_coordinates.x = player.position.x;
		ray[i].current_coordinates.y = player.position.y;
		ray[i].on_y = 0;
		if (player.position.x % TILE_SIZE == 0)
			ray[i].on_y = 1;
		ray[i].on_x = 0;
		if (player.position.y % TILE_SIZE == 0)
			ray[i].on_x = 1;
		ray[i].step_y = distance_to_x_axis(ray[i].on_x, ray[i].current_coordinates, ray[i].direction);
		ray[i].step_x = distance_to_y_axis(ray[i].on_y, ray[i].current_coordinates, ray[i].direction);
		ray[i].travelled_distance = 0;
		i++;
	}
}

void	keep_going(t_player player, t_ray *ray, char **map)
{
	int		wall_hit;
	int		number_of_steps;
	float	initial_distance_to_y;
	float	initial_distance_to_x;

	initial_distance_to_x = distance_to_x_axis(ray->on_x, player.position, player.direction);
	initial_distance_to_y = distance_to_y_axis(ray->on_y, player.position, player.direction);
	number_of_steps = 0;
	if (ray->travelled_distance == initial_distance_to_y)
		wall_hit = check_vertical_wall(ray->current_coordinates, ray->direction, map);
	else
		wall_hit = check_horizontal_wall(ray->current_coordinates, ray->direction, map);
	printf("wall hit: %d\n", wall_hit);
	while (wall_hit == 0)
	{
		if (initial_distance_to_y + number_of_steps * ray->step_x < initial_distance_to_x + number_of_steps * ray->step_y)
		{
			number_of_steps++;
			ray->travelled_distance = initial_distance_to_y + number_of_steps * ray->step_x;
			if (ray->on_y == 0)
			{
				if (ray->direction.x < 0)
					ray->current_coordinates.x = floor(ray->current_coordinates.x);
				else
					ray->current_coordinates.x = ceil(ray->current_coordinates.x);
				ray->on_y = 1;
			}
			else
			{
				if (ray->direction.x > 0)
					ray->current_coordinates.x += TILE_SIZE;
				else
					ray->current_coordinates.x -= TILE_SIZE;
			}
			ray->on_x = 0;
			wall_hit = check_vertical_wall(ray->current_coordinates, ray->direction, map);
		}
		else
		{
			number_of_steps++;
			ray->travelled_distance = initial_distance_to_x + number_of_steps * ray->step_y;
			if (ray->on_x == 0)
			{
				if (ray->direction.y < 0)
					ray->current_coordinates.y = floor(ray->current_coordinates.y);
				else
					ray->current_coordinates.y = ceil(ray->current_coordinates.y);
				ray->on_x = 1;
			}
			else
			{
				if (ray->direction.y > 0)
					ray->current_coordinates.y += TILE_SIZE;
				else
					ray->current_coordinates.y -= TILE_SIZE;
			}
			ray->on_y = 0;
			wall_hit = check_horizontal_wall(ray->current_coordinates, ray->direction, map);
		}
	}
}

void	first_step(t_ray *ray)
{
	if (distance_to_x_axis(ray->on_x, ray->current_coordinates, ray->direction) < distance_to_y_axis(ray->on_y, ray->current_coordinates, ray->direction))
	{
		ray->travelled_distance += distance_to_x_axis(ray->on_x, ray->current_coordinates, ray->direction);
		/*if (ray->direction.y < 0)
			ray->current_coordinates.y = ray->current_coordinates.y - (ray->current_coordinates.y % TILE_SIZE);
		else
			ray->current_coordinates.y = ray->current_coordinates.y - (ray->current_coordinates.y % TILE_SIZE) + TILE_SIZE;*/
		ray->on_x = 1;
	}
	else if (distance_to_y_axis(ray->on_y, ray->current_coordinates, ray->direction) < distance_to_x_axis(ray->on_x, ray->current_coordinates, ray->direction))
	{
		ray->travelled_distance += distance_to_y_axis(ray->on_y, ray->current_coordinates, ray->direction);
		/*if (ray->direction.x < 0)
			ray->current_coordinates.x = ray->current_coordinates.x - (ray->current_coordinates.x % TILE_SIZE);
		else
			ray->current_coordinates.x = ray->current_coordinates.x - (ray->current_coordinates.x % TILE_SIZE) + TILE_SIZE;*/
		ray->on_y = 1;
	}
	ray->step_x = calc_step_x(ray->direction, TILE_SIZE);
	ray->step_y = calc_step_y(ray->direction, TILE_SIZE);
}

int	start_dda(t_data *cub)
{
	first_step(&cub->ray[450]);
	keep_going(cub->player, &cub->ray[450], cub->map);
	/*printf("3 direction ray at %d, %d towards %f, %f on y: %d, on x: %d, step y: %f, step x: %f\n", cub->ray[450].current_coordinates.x, \
			cub->ray[450].current_coordinates.y, cub->ray[450].direction.x, cub->ray[450].direction.y, cub->ray[450].on_y, cub->ray[450].on_x, \
			cub->ray[450].step_x, cub->ray[450].step_y);*/
	//first_step(&cub->ray[0]);
/*	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{ 
		first_step(&cub->ray[i]);
		keep_going(cub->player, &cub->ray[i], cub->map);
		i++;
	}*/
	return (0);
}
