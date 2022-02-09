#include "../headers/cub3d.h"

float	ride_along_x(t_ray *ray, t_map *map, float *travelled_on_x)
{
	int	wall_hit;

	wall_hit = 0;
	ray->distance = *travelled_on_x;
	*travelled_on_x += ray->step_x;
	if (ray->direction.x > 0)
	{
		map->x += 1;
		if (map->map[map->y][map->x] == '1')
			wall_hit = wall_right;
	}
	else
	{
		map->x -= 1;
		if (map->map[map->y][map->x] == '1')
			wall_hit = wall_left;
	}
	return (wall_hit);
}

float	ride_along_y(t_ray *ray, t_map *map, float *travelled_on_y)
{
	int	wall_hit;

	wall_hit = 0;
	ray->distance = *travelled_on_y;
	*travelled_on_y += ray->step_y;
	if (ray->direction.y > 0)
	{
		map->y += 1;
		if (map->map[map->y][map->x] == '1')
			wall_hit = wall_above;
	}
	else
	{
		map->y -= 1;
		if (map->map[map->y][map->x] == '1')
			wall_hit = wall_below;
	}
	return (wall_hit);
}

void	get_impact_coordinates(t_ray *ray, t_vector player_position)
{
	float	delta_x;
	float	delta_y;

	if (ray->direction.x > 0)
		delta_x = ray->distance / ray->step_x;
	else
		delta_x = -ray->distance / ray->step_x;
	if (ray->direction.y > 0)
		delta_y = ray->distance / ray->step_y;
	else
		delta_y = -ray->distance / ray->step_y;
	ray->impact.x = player_position.x + delta_x;
	ray->impact.y = player_position.y + delta_y;
}

int	dda_algorithm(t_player player, t_ray *ray, t_map map)
{
	int		wall_type;
	float	travelled_on_y;
	float	travelled_on_x;

	travelled_on_y = distance_to_x_axis(player.position, ray->direction);
	travelled_on_x = distance_to_y_axis(player.position, ray->direction);
	map.x = (int)player.position.x;
	map.y = (int)player.position.y;
	wall_type = no_wall;
	while (wall_type == no_wall)
	{
		if (travelled_on_x < travelled_on_y)
			wall_type = ride_along_x(ray, &map, &travelled_on_x);
		else
			wall_type = ride_along_y(ray, &map, &travelled_on_y);
	}
	get_impact_coordinates(ray, player.position);
	return (wall_type);
}

int	start_dda(t_data *cub)
{
	int		i;
	int		j;
	int		wall_type;
	float	wall_height;

	i = 0;
	j = 0;
	while (i < WIN_WIDTH)
	{
		wall_type = dda_algorithm(cub->player, &cub->ray[i], cub->map);
		if (i < WIN_WIDTH / 2)
			wall_height = calc_projected_wall_height(cub->ray[i].distance, ((FOV / 2) - (i * ANGLE_PER_PIXEL)));
		else
		{
			//printf("current angle to end: %f, distortion angle: %f\n", FOV - i * ANGLE_PER_PIXEL, j * ANGLE_PER_PIXEL);
			wall_height = calc_projected_wall_height(cub->ray[i].distance, (j * ANGLE_PER_PIXEL));
			j++;
		}
		if (i == 0)
		{
			draw_floor(cub);
			draw_ceiling(cub);
		}
		ft_print_texture(cub, wall_height, wall_type, i);
		if (i == WIN_WIDTH - 1)
		{
			ft_draw_minimap(cub);
			ft_draw_frame(cub);
		}
		i++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
	return (0);
}
