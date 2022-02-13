#include "../../headers/cub3d.h"

int	check_horizontal_wall(t_vector position, t_vector direction, char **map)
{
	int	coord_x;
	int	coord_y;

	coord_x = floor(position.x);
	coord_y = floor(position.y);
	if (direction.y <= 0 && coord_y > 0)
	{
		if ((map[coord_y - 1][coord_x] == '1' || map[coord_y - 1][coord_x] == '2')
				&& position.y - floorf(position.y) < PLAYER_SPEED)
			return (north_wall);
	}
	else if (direction.y >= 0 && coord_y < get_map_height(map)
		&& (1 - (position.y - floorf(position.y)) < PLAYER_SPEED))
	{
		if (map[coord_y + 1][coord_x] == '1' || map[coord_y + 1][coord_x] == '2')
			return (south_wall);
	}
	return (no_wall);
}

int	check_vertical_wall(t_vector position, t_vector direction, char **map)
{
	int	coord_x;
	int	coord_y;

	coord_x = floor(position.x);
	coord_y = floor(position.y);
	if (direction.x <= 0 && coord_x > 0)
	{
		if ((map[coord_y][coord_x - 1] == '1'  || map[coord_y][coord_x - 1] == '2')
				&& position.x - floorf(position.x) < PLAYER_SPEED)
			return (west_wall);
	}
	else if (direction.x >= 0 && coord_x < (int)ft_strlen(map[coord_y])
		&& (1 - (position.x - floorf(position.x)) < PLAYER_SPEED))
	{
		if (map[coord_y][coord_x + 1] == '1' || map[coord_y][coord_x + 1] == '2')
			return (east_wall);
	}
	return (no_wall);
}

void	move(t_vector mov_direction, t_player *player, char **map)
{
	if (check_vertical_wall(player->pos, mov_direction, map) == no_wall)
		player->pos.x += mov_direction.x * PLAYER_SPEED;
	if (check_horizontal_wall(player->pos, mov_direction, map) == no_wall)
		player->pos.y += mov_direction.y * PLAYER_SPEED;
}

int	move_player(int keycode, t_data *cub)
{
	t_vector	movement_direction;

	if (keycode == KEY_W)
		movement_direction = cub->player.direction;
	else if (keycode == KEY_A)
		movement_direction = rotate_vector(cub->player.direction, -(M_PI / 2));
	else if (keycode == KEY_S)
		movement_direction = rotate_vector(cub->player.direction, M_PI);
	else
		movement_direction = rotate_vector(cub->player.direction, M_PI / 2);
	move(movement_direction, &cub->player, cub->map.map);
	return (0);
}
