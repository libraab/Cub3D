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
			wall_hit = wall_above;
	}
	else
	{
		map->x -= 1;
		if (map->map[map->y][map->x] == '1')
			wall_hit = wall_below;
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

void	get_impact_coordinates(t_ray *ray, t_coordinates player_position)
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
	int		wall_hit;
	float	travelled_on_y;
	float	travelled_on_x;

	travelled_on_y = distance_to_x_axis(player.position, ray->direction);
	travelled_on_x = distance_to_y_axis(player.position, ray->direction);
	map.x = (int)player.position.x;
	map.y = (int)player.position.y;
	wall_hit = no_wall;
	while (wall_hit == no_wall)
	{
		if (travelled_on_x < travelled_on_y)
			wall_hit = ride_along_x(ray, &map, &travelled_on_x);
		else
			wall_hit = ride_along_y(ray, &map, &travelled_on_y);
	}
	get_impact_coordinates(ray, player.position);
	return (wall_hit);
}

int	start_dda(t_data *cub)
{
	int	i;
	i = 0;
	while (i < WIN_WIDTH)
	{
		 dda_algorithm(cub->player, &cub->ray[i], cub->map);
		ft_put_img2(&cub->sheet, DEEP_PINK, cub->ray[i].impact.y * 10, cub->ray[i].impact.x * 10);
	//	wall_height = calc_projected_wall_height(fmax(cub->ray[i].travelled_on_y, cub->ray[i].travelled_on_x));
	//	printf("height for ray %d: %f\n", i, wall_height);
		//ft_print_texture(cub, dda_algorithm(cub->player, &cub->ray[i], cub->map));
		i++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
	return (0);
}
