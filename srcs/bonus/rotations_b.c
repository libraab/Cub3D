/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:23:53 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 15:18:25 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	rotate_player(int keycode, t_data *cub)
{
	float	rotation_angle_keyboard;
	float	rotation_angle_mouse;

	rotation_angle_keyboard = M_PI / 20;
	rotation_angle_mouse = M_PI / 30;
	if (keycode == KEY_ARROW_LEFT)
		cub->player.direction = rotate_vector(cub->player.direction,
				-rotation_angle_keyboard);
	if (keycode == KEY_ARROW_RIGHT)
		cub->player.direction = rotate_vector(cub->player.direction,
				rotation_angle_keyboard);
	if (keycode == 100)
		cub->player.direction = rotate_vector(cub->player.direction,
				rotation_angle_mouse);
	if (keycode == 101)
		cub->player.direction = rotate_vector(cub->player.direction,
				-rotation_angle_mouse);
	return (0);
}

t_vector	rotate_vector(t_vector to_rotate, float angle)
{
	t_vector	rotated;

	rotated.x = to_rotate.x * cos(angle) - to_rotate.y * sin(angle);
	rotated.y = to_rotate.x * sin(angle) + to_rotate.y * cos(angle);
	return (rotated);
}
