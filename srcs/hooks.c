/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:50:45 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/27 11:51:43 by abouhlel         ###   ########.fr       */
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
	{
		cub->player.direction = rotate_vector(cub->player.direction, -ROTATION_ANGLE);
		cast_rays(cub->rays, cub->player.direction);
		draw_fov(cub->rays, cub, GOLD);
	}
	if (keycode == KEY_ARROW_RIGHT)
	{
		cub->player.direction = rotate_vector(cub->player.direction, ROTATION_ANGLE);
		cast_rays(cub->rays, cub->player.direction);
		draw_fov(cub->rays, cub, BLUE);
	}
	return (0);
}

int	player_movement(int keycode, t_data *cub)
{
	if (keycode == KEY_ARROW_LEFT || keycode == KEY_ARROW_RIGHT)
		rotate_player(keycode, cub);
	if (keycode == KEY_W || keycode == KEY_A \
			|| keycode == KEY_S || keycode == KEY_D)
		move_player(keycode, cub);
	return (0);
}
