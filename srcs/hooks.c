/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:50:45 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/30 17:20:23 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	ft_exit(void)
{
	write(1, "Bye Bye!\n", 9);
	exit(0);
}

int	key_release(int keycode)
{
	if (keycode == KEY_ECHAP)
		ft_exit();
	return (0);
}

int	rotate_player(int keycode, t_data *cub)
{
	if (keycode == KEY_ARROW_LEFT)
		cub->player.direction = rotate_vector(cub->player.direction, -ROTATION_ANGLE);
	if (keycode == KEY_ARROW_RIGHT)
		cub->player.direction = rotate_vector(cub->player.direction, ROTATION_ANGLE);
	return (0);
}

int	rotation_key(int keycode)
{
	if (keycode == KEY_ARROW_LEFT || keycode == KEY_ARROW_RIGHT)
		return (keycode);
	else
		return (0);
}

int	movement_key(int keycode)
{
	if (keycode == KEY_W || keycode == KEY_A \
			|| keycode == KEY_S || keycode == KEY_D)
		return (keycode);
	else
		return (0);
}

int	can_move_vertically(t_vector position, t_vector direction, char **map)
{
	int	coord_x;
	int	coord_y;

	coord_x = (int)position.x / TILE_SIZE;
	coord_y = (int)position.y / TILE_SIZE;
	if (map[coord_y][coord_x] == '0' || ft_is_direction(map[coord_y][coord_x]))
	{
		if (direction.y > 0 && map[coord_y + 1][coord_x] == '1')
			return (0);
		else if (direction.y < 0 && map[coord_y - 1][coord_x] == '1')
			return (0);
	}
	return (1);
}

int	can_move_horizontally(t_vector position, t_vector direction, char **map)
{
	int	coord_x;
	int	coord_y;

	coord_x = (int)position.x / TILE_SIZE;
	coord_y = (int)position.y / TILE_SIZE;
	if (map[coord_y][coord_x] == '0' || ft_is_direction(map[coord_y][coord_x]))
	{
		if (direction.x > 0 && map[coord_y][coord_x + 1] == '1')
			return (0);
		else if (direction.x < 0 && map[coord_y][coord_x - 1] == '1')
			return (0);
	}
	return (1);
}

int	player_movement(int keycode, t_data *cub)
{
	int	coord_x = (int)cub->player.position.x / TILE_SIZE;
	int	coord_y = (int)cub->player.position.y / TILE_SIZE;
	printf("tile %c is at coordinates %d, %d, tile above: %c, tile below: %c, tile to the right: %c, tile to the left: %c\n", cub->map[coord_y][coord_x], coord_x, coord_y, cub->map[coord_y - 1][coord_x], cub->map[coord_y + 1][coord_x], cub->map[coord_y][coord_x + 1], cub->map[coord_y][coord_x - 1]);
	if (keycode == rotation_key(keycode) || keycode == movement_key(keycode))
	{
		if (keycode == rotation_key(keycode))
			rotate_player(keycode, cub);
		if (keycode == movement_key(keycode))
			move_player(keycode, cub);
		cast_rays(cub->rays, cub->player);
		start_dda(cub);
	}
	return (0);
}
