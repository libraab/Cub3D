/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:45:21 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/26 18:13:19 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_vector	starting_direction(char player_character)
{
	t_vector	direction;

	direction.x = 0;
	direction.y = 0;
	if (player_character == 'N')
	{
		direction.x = 0;
		direction.y = -1;
	}
	else if (player_character == 'E')
	{
		direction.x = 1;
		direction.y = 0;
	}
	else if (player_character == 'S')
	{
		direction.x = 0;
		direction.y = 1;
	}
	else if (player_character == 'W')
	{
		direction.x = -1;
		direction.y = 0;
	}
	return (direction);
}

t_vector	rotate_vector(t_vector to_rotate, float angle)
{
	t_vector	rotated;

	rotated.x = to_rotate.x * cos(angle) - to_rotate.y * sin(angle);
	rotated.y = to_rotate.x * sin(angle) + to_rotate.y * cos(angle);
	return (rotated);
}

void	cast_rays(t_ray rays[WIN_WIDTH], t_vector player_direction)
{
	int	i;

	rays[0].direction = rotate_vector(player_direction, -(FOV / 2));
	i = 1;
	while (i < WIN_WIDTH)
	{
		rays[i].direction = rotate_vector(rays[i - 1].direction, ANGLE_PER_PIXEL);
		rays[i].step_x = calc_step_x(rays[i].direction, 1);
		rays[i].step_y = calc_step_y(rays[i].direction, 1);
		i++;
	}
}

float	first_step_to_x_axis(t_player player, t_vector ray_direction)
{
	float	offset;
	float	first_step;

	if (ray_direction.y == 0)
		return (FLT_MAX);
	else if (ray_direction.y > 0)
		offset = ceil(player.position.y) - player.position.y;
	else
		offset = player.position.y - floor(player.position.y);
	first_step = calc_step_y(ray_direction, offset);
	return (first_step);
}

float	first_step_to_y_axis(t_player player, t_vector ray_direction)
{
	float	offset;
	float	first_step;

	if (ray_direction.x == 0)
		return (FLT_MAX);
	else if (ray_direction.x > 0)
		offset = ceil(player.position.x) - player.position.x;
	else
		offset = player.position.x - floor(player.position.x);
	first_step = calc_step_x(ray_direction, offset);
	return (first_step);
}
