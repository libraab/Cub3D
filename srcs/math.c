#include "../headers/cub3d.h"

float	calc_step_x(t_direction ray_direction, float x_component)
{
	float	step;

	if (ray_direction.x != 0)
		step = x_component * sqrt(1 + (ray_direction.y * ray_direction.y) / (ray_direction.x * ray_direction.x));
	else
		step = FLT_MAX;
	return (step);
}

float	calc_step_y(t_direction ray_direction, float y_component)
{
	float	step;

	if (ray_direction.y != 0)
		step = y_component * sqrt(1 + (ray_direction.x * ray_direction.x) / (ray_direction.y * ray_direction.y));
	else
		step = FLT_MAX;
	return (step);
}

float	distance_to_x_axis(t_coordinates position, t_direction direction)
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

float	distance_to_y_axis(t_coordinates position, t_direction direction)
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

	i = 0;
	while (i < WIN_WIDTH)
	{
		if (i == 0)
			ray[i].direction = rotate_vector(player.direction, -(FOV / 2));
		else if (i != WIN_WIDTH / 2)
			ray[i].direction = rotate_vector(ray[i - 1].direction, ANGLE_PER_PIXEL);
		else
			ray[i].direction = player.direction;
		ray[i].step_x = calc_step_x(ray[i].direction, 1);
		ray[i].step_y = calc_step_y(ray[i].direction, 1);
		ray[i].travelled_distance = 0;
		i++;
	}
}

int	in_map(char **map, int x, int y)
{
	if (x >= 0 && y >= 0 && y < get_map_height(map) && x < (int)ft_strlen(map[y]))
		return (1);
	return (0);
}

int	ray_ver_wall(int coord_y, int coord_x, t_direction direction, char **map)
{
	if (in_map(map, coord_x, coord_y) && in_map(map, coord_x - 1, coord_y))
		printf("map coordinates: %d, %d  tile: %c, left tile: %c\n", coord_y, coord_x, map[coord_y][coord_x], map[coord_y][coord_x - 1]);
	else
	{
		sleep(1);
		printf("map coordinates: %d, %d\n", coord_y, coord_x);
		printf("out of bounds\n");
		return (no_wall);
	}
	if (direction.x < 0 && in_map(map, coord_x, coord_y))
	{
		if (map[coord_y][coord_x] == '1')
			return (wall_left);
	}
	else if (direction.x > 0 && in_map(map, coord_x, coord_y))
	{
		if (map[coord_y][coord_x] == '1')
			return (wall_right);
	}
	return (no_wall);
}

int	ray_hor_wall(int coord_y, int coord_x, t_direction direction, char **map)
{
	(void)direction;
	if (in_map(map, coord_x, coord_y) && in_map(map, coord_x, coord_y - 1))
		;
	else
	{
		sleep(1);
		printf("map coordinates: %d, %d\n", coord_y, coord_x);
		printf("out of bounds\n");
		return (no_wall);
	}
	if (direction.y < 0 && in_map(map, coord_x, coord_y))
	{
		if (map[coord_y][coord_x] == '1')
			return (wall_above);
	}
	else if (direction.y > 0 && in_map(map, coord_x, coord_y))
	{
		if (map[coord_y][coord_x] == '1')
			return (wall_below);
	}
	return (no_wall);
}
