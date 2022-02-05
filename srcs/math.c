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

int	in_map(char **map, int x, int y)
{
	if (x >= 0 && y >= 0 && y <= get_map_height(map) && x < (int)ft_strlen(map[y]))
		return (1);
	return (0);
}

int	ray_ver_wall(t_coordinates position, t_vector direction, char **map)
{
	int	coord_x;
	int	coord_y;

	coord_x = (position.x - position.x % TILE_SIZE) / TILE_SIZE;
	coord_y = (position.y - position.y % TILE_SIZE) / TILE_SIZE;
	if (direction.x <= 0 && in_map(map, coord_x, coord_y))
	{
		printf("check 1: x %d, y %d, tile %c\n", coord_x, coord_y, map[coord_y][coord_x]);
		if (map[coord_y][coord_x] == '1')
			return (wall_left);
	}
	else if (direction.x >= 0 && in_map(map, coord_x, coord_y))
	{
		printf("check 2: x %d, y %d, tile %c\n", coord_x, coord_y, map[coord_y][coord_x]);
		 if (map[coord_y][coord_x] == '1')
			return (wall_right);
	}
	return (no_wall);

}

int	ray_hor_wall(t_coordinates position, t_vector direction, char **map)
{
	int	coord_x;
	int	coord_y;

	coord_x = (position.x - position.x % TILE_SIZE) / TILE_SIZE;
	coord_y = (position.y - position.y % TILE_SIZE) / TILE_SIZE;
	if (direction.y <= 0 && in_map(map, coord_x, coord_y))
	{
		printf("check 3: x %d, y %d, tile %c\n", coord_x, coord_y, map[coord_y][coord_x]);
		if (map[coord_y][coord_x] == '1')
			return (wall_above);
	}
	else if (direction.y >= 0 && in_map(map, coord_x, coord_y))
	{
		printf("check 4: x %d, y %d, tile %c\n", coord_x, coord_y, map[coord_y][coord_x]);
		if (map[coord_y][coord_x] == '1')
			return (wall_below);
	}
	return (no_wall);
}

void	keep_going(t_player player, t_ray *ray, char **map)
{
	int		wall_hit;
	int		number_of_steps;
	float	initial_distance_to_y;
	float	initial_distance_to_x;

	initial_distance_to_x = distance_to_x_axis(ray->on_x, ray->current_coordinates, ray->direction);
	initial_distance_to_y = distance_to_y_axis(ray->on_y, ray->current_coordinates, ray->direction);
	number_of_steps = 0;
	wall_hit = 0;
	while (wall_hit == 0)
	{
		if (initial_distance_to_y + number_of_steps * ray->step_x < initial_distance_to_x + number_of_steps * ray->step_y)
		{
			ray->travelled_distance = initial_distance_to_y + number_of_steps * ray->step_x;
			ray->current_coordinates.x = player.position.x + ray->travelled_distance * ray->direction.x;
			ray->current_coordinates.y = player.position.y + ray->travelled_distance * ray->direction.y;
			wall_hit = ray_ver_wall(ray->current_coordinates, ray->direction, map);
		}
		else
		{
			ray->travelled_distance = initial_distance_to_x + number_of_steps * ray->step_y;
			ray->current_coordinates.x = player.position.x + ray->travelled_distance * ray->direction.x;
			ray->current_coordinates.y = player.position.y + ray->travelled_distance * ray->direction.y;
			wall_hit = ray_hor_wall(ray->current_coordinates, ray->direction, map);
		}
		if (number_of_steps == 0)
		{
			ray->step_x = calc_step_x(ray->direction, TILE_SIZE);
			ray->step_y = calc_step_y(ray->direction, TILE_SIZE);
		}
		number_of_steps++;
		printf("loop\n");
	}
	printf("wall %d hit at a distance of %f\n", wall_hit, ray->travelled_distance);
}

int	start_dda(t_data *cub)
{
	keep_going(cub->player, &cub->ray[450], cub->map);
	/*printf("3 direction ray at %d, %d towards %f, %f on y: %d, on x: %d, step y: %f, step x: %f\n", cub->ray[450].current_coordinates.x, \
			cub->ray[450].current_coordinates.y, cub->ray[450].direction.x, cub->ray[450].direction.y, cub->ray[450].on_y, cub->ray[450].on_x, \
			cub->ray[450].step_x, cub->ray[450].step_y);*/
/*	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{ 
		keep_going(cub->player, &cub->ray[i], cub->map);
		i++;
	}*/
	return (0);
}
