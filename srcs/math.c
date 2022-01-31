/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:45:21 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/31 22:09:20 by bleotard         ###   ########.fr       */
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

float	distance_to_x_axis(int on_x, t_vector position, t_vector direction)
{
	float	offset;
	float	first_step;


	if (on_x == 1)
		return (0);
	else if (direction.y == 0)
		return (FLT_MAX);
	else if (direction.y > 0)
		offset = ceil(position.y) - position.y;
	else
		offset = position.y - floor(position.y);
	first_step = calc_step_y(direction, offset);
	return (first_step);
}

float	distance_to_y_axis(int on_y, t_vector position, t_vector direction)
{
	float	offset;
	float	first_step;

	if (on_y == 1)
		return (0);
	else if (direction.x == 0)
		return (FLT_MAX);
	else if (direction.x > 0)
		offset = ceil(position.x) - position.x;
	else
		offset = position.x - floor(position.x);
	first_step = calc_step_x(direction, offset);
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
		else if (i != WIN_WIDTH / 2)
			rays[i].direction = rotate_vector(rays[i - 1].direction, ANGLE_PER_PIXEL);
		else
			rays[i].direction = player.direction;
		rays[i].current_coordinates = player.position;
		rays[i].on_y = 0;
		if ((int)player.position.x % TILE_SIZE == 0 && (int)player.position.x - player.position.x == 0)
			rays[i].on_y = 1;
		rays[i].on_x = 0;
		if ((int)player.position.y % TILE_SIZE == 0 && (int)player.position.y - player.position.y == 0)
			rays[i].on_x = 1;
		rays[i].step_y = distance_to_y_axis(rays[i].on_y, rays[i].current_coordinates, rays[i].direction);
		rays[i].step_x = distance_to_x_axis(rays[i].on_x, rays[i].current_coordinates, rays[i].direction);
		rays[i].travelled_distance = 0;
		i++;
	}
	printf("INITIAL RAY STATS:\n");
	printf("pos: %f, %f, dir: %f, %f on x: %d on y: %d distance to x: %f, distance to y: %f\n", \
			  rays[250].current_coordinates.x, rays[250].current_coordinates.y, rays[250].direction.x, rays[250].direction.y,\
			  rays[250].on_x, rays[250].on_y, rays[250].step_x, rays[250].step_y);
}

void	keep_going(t_player player, t_ray *ray, char **map)
{
	int		wall_hit;
	int		number_of_steps;
	float	initial_distance_to_y;
	float	initial_distance_to_x;

//	printf("START OF DDA RAY STATS:\n");
//	printf("pos: %f, %f, dir: %f, %f on x: %d, on y: %d, distance travelled: %f, step x: %f, step y: %f\n", \
		//	ray->current_coordinates.x, ray->current_coordinates.y, ray->direction.x, ray->direction.y, ray->on_x, ray->on_y, \
		//	ray->travelled_distance, ray->step_x, ray->step_y);
	initial_distance_to_y = distance_to_y_axis(ray->on_y, player.position, player.direction);
	initial_distance_to_x = distance_to_x_axis(ray->on_x, player.position, player.direction);
	number_of_steps = 0;
	wall_hit = check_vertical_wall(ray->current_coordinates, ray->direction, map);
	if (wall_hit == 0)
		wall_hit = check_horizontal_wall(ray->current_coordinates, ray->direction, map);
	while (wall_hit == 0)
	{
		if (initial_distance_to_y + number_of_steps * ray->step_x < initial_distance_to_x + number_of_steps * ray->step_y)
		{
			number_of_steps++;
			ray->travelled_distance = initial_distance_to_y + number_of_steps * ray->step_x;
//			printf("distance travelled after %d steps taken: %f\n", number_of_steps, ray->travelled_distance);
			if (ray->on_y == 0)
			{
				if (ray->direction.x < 0)
					ray->current_coordinates.x = floor(ray->current_coordinates.x);
				else
					ray->current_coordinates.x = ceil(ray->current_coordinates.x);
				ray->on_y = 1;
			}
			else
			{
				if (ray->direction.x > 0)
					ray->current_coordinates.x += TILE_SIZE;
				else
					ray->current_coordinates.x -= TILE_SIZE;
			}
			ray->on_x = 0;
			wall_hit = check_vertical_wall(ray->current_coordinates, ray->direction, map);
//			printf("hit coordinates: %f, %f\n", ray->current_coordinates.x, ray->current_coordinates.y);
		}
		else
		{
			number_of_steps++;
			ray->travelled_distance = initial_distance_to_x + number_of_steps * ray->step_y;
//			printf("distance travelled after %d steps taken: %f\n", number_of_steps, ray->travelled_distance);
			if (ray->on_x == 0)
			{
				if (ray->direction.y < 0)
					ray->current_coordinates.y = floor(ray->current_coordinates.y);
				else
					ray->current_coordinates.y = ceil(ray->current_coordinates.y);
				ray->on_x = 1;
			}
			else
			{
				if (ray->direction.y > 0)
					ray->current_coordinates.y += TILE_SIZE;
				else
					ray->current_coordinates.y -= TILE_SIZE;
			}
			ray->on_y = 0;
			wall_hit = check_horizontal_wall(ray->current_coordinates, ray->direction, map);
//			printf("hit coordinates: %f, %f\n", ray->current_coordinates.x, ray->current_coordinates.y);
		}
	}
//	printf("wall hit: %d\n\n", wall_hit);
}

void	first_step(t_ray *ray)
{
	if (distance_to_x_axis(ray->on_x, ray->current_coordinates, ray->direction) < distance_to_y_axis(ray->on_y, ray->current_coordinates, ray->direction))
	{
		ray->travelled_distance += distance_to_x_axis(ray->on_x, ray->current_coordinates, ray->direction);
		if (ray->direction.y < 0)
			ray->current_coordinates.y = floor(ray->current_coordinates.y);
		else
			ray->current_coordinates.y = ceil(ray->current_coordinates.y);
		ray->on_x = 1;
	}
	else if (distance_to_y_axis(ray->on_y, ray->current_coordinates, ray->direction) < distance_to_x_axis(ray->on_x, ray->current_coordinates, ray->direction))
	{
		ray->travelled_distance += distance_to_y_axis(ray->on_y, ray->current_coordinates, ray->direction);
		if (ray->direction.x < 0)
			ray->current_coordinates.x = floor(ray->current_coordinates.x);
		else
			ray->current_coordinates.x = ceil(ray->current_coordinates.x);
		ray->on_y = 1;
	}
	ray->step_x = calc_step_x(ray->direction, 1);
	ray->step_y = calc_step_y(ray->direction, 1);
}

int	start_dda(t_data *cub)
{
	//first_step(&cub->rays[250]);
	//keep_going(cub->player, &cub->rays[250], cub->map);
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{ 
		first_step(&cub->rays[i]);
		keep_going(cub->player, &cub->rays[i], cub->map);
		i++;
	}
//	printf("unit step x: %f, unit step y: %f\n", cub->rays[250].step_x, cub->rays[250].step_y);
	return (0);
}
