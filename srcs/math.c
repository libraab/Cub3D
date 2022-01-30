/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:45:21 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/30 17:11:12 by bleotard         ###   ########.fr       */
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

float	distance_to_x_axis(t_ray ray)
{
	float	offset;
	float	first_step;

	if (ray.direction.y == 0)
		return (FLT_MAX);
	else if (ray.direction.y > 0)
		offset = ceil(ray.current_coordinates.y) - ray.current_coordinates.y;
	else
		offset = ray.current_coordinates.y - floor(ray.current_coordinates.y);
	first_step = calc_step_y(ray.direction, offset);
	return (first_step);
}

float	distance_to_y_axis(t_ray ray)
{
	float	offset;
	float	first_step;

	if (ray.direction.x == 0)
		return (FLT_MAX);
	else if (ray.direction.x > 0)
		offset = ceil(ray.current_coordinates.x) - ray.current_coordinates.x;
	else
		offset = ray.current_coordinates.x - floor(ray.current_coordinates.x);
	first_step = calc_step_x(ray.direction, offset);
	return (first_step);
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

void	cast_rays(t_ray rays[WIN_WIDTH], t_player player)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		if (i == 0)
			rays[i].direction = rotate_vector(player.direction, -(FOV / 2));
		else
			rays[i].direction = rotate_vector(rays[i - 1].direction, ANGLE_PER_PIXEL);
		rays[i].current_coordinates = player.position;
		rays[i].step_y = distance_to_y_axis(rays[i]);
		rays[i].step_x = distance_to_x_axis(rays[i]);
		rays[i].travelled_distance = 0;
		i++;
	}
}

int	check_vertical_wall(t_ray ray, char **map)
{
	int	coord_x;
	int	coord_y;

	coord_y = (int)ray.current_coordinates.y / TILE_SIZE;
	if (ray.direction.x > 0)
	{
		coord_x =  (int)ray.current_coordinates.x / TILE_SIZE;
		if (map[coord_y][coord_x] && map[coord_y][coord_x] == '1')
			return (1);
	}	
	else
		coord_x =  (int)ray.current_coordinates.x / TILE_SIZE;
	return (1);
}

int	check_horizontal_wall(t_ray ray, char **map)
{
	int	coord_x;
	int	coord_y;

	(void)map;
	coord_x =  (int)ray.current_coordinates.x / TILE_SIZE;
	if (ray.direction.y > 0)
		coord_y =  (int)ray.current_coordinates.y / TILE_SIZE;
	else
		coord_y =  (int)ray.current_coordinates.y / TILE_SIZE;
	return (1);
}

void	keep_going(t_ray ray, char **map)
{
	int		wall_hit;
	int		number_of_steps;
	float	initial_distance_to_y;
	float	initial_distance_to_x;

	initial_distance_to_y = distance_to_y_axis(ray);
	initial_distance_to_x = distance_to_x_axis(ray);
	wall_hit = check_vertical_wall(ray, map);
	wall_hit = check_horizontal_wall(ray, map);
	number_of_steps = 0;
	while (wall_hit == 0)
	{
		if (initial_distance_to_y + number_of_steps * ray.step_x < initial_distance_to_x + number_of_steps * ray.step_y)
		{
			ray.travelled_distance = initial_distance_to_y + number_of_steps * ray.step_x;
			number_of_steps++;
		//	ray.current_coordinates.y++;
		//	wall_hit = check_vertical_wall(ray);
		}
		else
		{
			ray.travelled_distance = initial_distance_to_x + number_of_steps * ray.step_y;
			number_of_steps++;
		//	ray.current_coordinates.x++;
		//	wall_hit = check_horizontal_wall(ray);
		}
	}
}

void	first_step(t_ray ray)
{
	if (distance_to_x_axis(ray) < distance_to_y_axis(ray))
	{
		ray.travelled_distance += distance_to_x_axis(ray);
		if (ray.direction.y < 0)
			ray.current_coordinates.y = floor(ray.current_coordinates.y);
		else
			ray.current_coordinates.y = ceil(ray.current_coordinates.y);
	}
	else
	{
		ray.travelled_distance += distance_to_y_axis(ray);
		if (ray.direction.x < 0)
			ray.current_coordinates.x = floor(ray.current_coordinates.x);
		else
			ray.current_coordinates.x = ceil(ray.current_coordinates.x);
	}
	ray.step_x = calc_step_x(ray.direction, 1);
	ray.step_y = calc_step_y(ray.direction, 1);
}

int	start_dda(t_data *cub)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{ 
		first_step(cub->rays[i]);
		keep_going(cub->rays[i], cub->map);
		i++;
	}
	return (0);
}
