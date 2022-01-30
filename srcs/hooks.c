/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:50:45 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/30 04:37:24 by bleotard         ###   ########.fr       */
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
	if (position.y > 0 && position.y / TILE_SIZE < 1 && direction.y < 0)
				return (0);
	if (position.y > 0 && ft_tablen(map) - position.y / TILE_SIZE < 1 && direction.y > 0)
				return (0);
	return (1);
}

int	can_move_horizontally(t_vector position, t_vector direction, char **map)
{
	int	i;

	i = 0;
	while (i < ft_tablen(map))
	{
		if (((int)position.y / TILE_SIZE) == i)
		{
			if (position.x / TILE_SIZE < 1 && direction.x < 0)
				return (0);
			if (ft_strlen(map[i]) - position.x / TILE_SIZE < 1 && direction.x > 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	player_movement(int keycode, t_data *cub)
{
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
