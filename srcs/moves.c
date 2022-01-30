/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 09:37:49 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/30 21:19:39 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	calc_deltas(t_vector direction, float *delta_x, float *delta_y, float distance)
{
	float		step_x;
	float		step_y;

	step_x = calc_step_x(direction, 1);
	step_y = calc_step_y(direction, 1);
	*delta_x = distance / step_x;
	*delta_y = distance / step_y;
}

void	move(t_vector movement_direction, t_player *player, char **map)
{
	float		delta_x;
	float		delta_y;

	calc_deltas(movement_direction, &delta_x, &delta_y, PLAYER_STEP);
	if (check_vertical_wall(player->position, movement_direction, map) == no_wall)
	{
		if (movement_direction.x > 0)
			player->position.x += delta_x;
		else
			player->position.x -= delta_x;
	}
	if (check_horizontal_wall(player->position, movement_direction, map) == no_wall)
	{
		if (movement_direction.y > 0)
			player->position.y += delta_y;
		else
			player->position.y -= delta_y;
	}
}

void	move_forward(t_player *player, char **map)
{
	t_vector	movement_direction;

	movement_direction = player->direction;
	move(movement_direction, player, map);
}

void	move_left(t_player *player, char **map)
{
	t_vector	movement_direction;

	movement_direction = rotate_vector(player->direction, -(M_PI / 2));
	move(movement_direction, player, map);
}

void	move_right(t_player *player, char **map)
{
	t_vector	movement_direction;

	movement_direction = rotate_vector(player->direction, M_PI / 2);
	move(movement_direction, player, map);
}

void	move_back(t_player *player, char **map)
{
	t_vector	movement_direction;

	movement_direction = rotate_vector(player->direction, M_PI);
	move(movement_direction, player, map);
}

int	move_player(int keycode, t_data *cub)
{
	if (keycode == KEY_W)
		move_forward(&cub->player, cub->map);
	else if (keycode == KEY_A)
		move_left(&cub->player, cub->map);
	else if (keycode == KEY_S)
		move_back(&cub->player, cub->map);
	else if (keycode == KEY_D)
		move_right(&cub->player, cub->map);
	ft_draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
	return (0);
}
