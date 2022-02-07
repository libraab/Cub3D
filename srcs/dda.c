#include "../headers/cub3d.h"

int	dda_algorithm(t_player player, t_ray *ray, t_map map)
{
	int		wall_hit;
	float			total_travelled;

	ray->travelled_on_y = distance_to_x_axis(player.position, ray->direction);
	ray->travelled_on_x = distance_to_y_axis(player.position, ray->direction);
	map.x = (int)player.position.x;
	map.y = (int)player.position.y;
	/*if (ray->direction.y == 1 || ray->direction.y == -1)
			wall_hit = ray_ver_wall(map_coord, ray->direction, map);
	else
			wall_hit = ray_hor_wall(map_coord, ray->direction, map);*/
	wall_hit = no_wall;
	total_travelled = 0;
	while (wall_hit == no_wall)
	{
		if (ray->travelled_on_x < ray->travelled_on_y)
		{
			ray->travelled_on_x += ray->step_x;
			total_travelled = ray->travelled_on_x;
			printf("on x so far: %f\n", ray->travelled_on_x);
			if (ray->direction.x > 0) // direction vers droite ou diagonal droite (up & down)
			{
				map.x += 1;
				if (map.map[map.y][map.x] == '1')
					wall_hit = wall_left;
			}
			else
			{
				map.x -= 1;
				if (map.map[map.y][map.x] == '1')
					wall_hit = wall_right;
			}
		}
		else
		{
			ray->travelled_on_y += ray->step_y;
			total_travelled = ray->travelled_on_y;
			printf("on y so far: %f\n", ray->travelled_on_y);
			if (ray->direction.y > 0)
			{
				map.y += 1;
				if (map.map[map.y][map.x] == '1')
				wall_hit = wall_above;
			}
			else
			{
				map.y -= 1;
				if (map.map[map.y][map.x] == '1')
					wall_hit = wall_below;
			}
		}
	}
	float	delta_x;
	float	delta_y;

	if (ray->direction.x > 0)
		delta_x = total_travelled / ray->step_x - 1;
	else
		delta_x = -total_travelled / ray->step_x + 1;
	if (ray->direction.y > 0)
		delta_y = total_travelled / ray->step_y - 1;
	else
		delta_y = -total_travelled / ray->step_y + 1;
	ray->impact.x = player.position.x + delta_x;
	ray->impact.y = player.position.y + delta_y;
	printf("wall %d at %f distance\n", wall_hit, total_travelled);
	printf("map coordinates: %d, %d    impact coordinates: %f, %f\n", map.y, map.x, ray->impact.y, ray->impact.x);
	return (wall_hit);
}

int	start_dda(t_data *cub)
{
//	float	wall_height;
	 dda_algorithm(cub->player, &cub->ray[450], cub->map);
	//wall_height = calc_projected_wall_height(fmax(cub->ray[450].travelled_on_y, cub->ray[450].travelled_on_x));
	// mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
/*	int	i;
	//printf("player position: %f, %f   ray 450 step: %f, %f   ray 450 direction: %f, %f\n", cub->player.position.x, cub->player.position.y, cub->ray[450].step_x, cub->ray[450].step_y, cub->ray[450].direction.x, cub->ray[450].direction.y);
	//dda_algorithm(cub->player, &cub->ray[450], cub->map);
	i = 0;
	while (i < WIN_WIDTH)
	{
		 dda_algorithm(cub->player, &cub->ray[i], cub->map);
		wall_height = calc_projected_wall_height(fmax(cub->ray[i].travelled_on_y, cub->ray[i].travelled_on_x));
		printf("height for ray %d: %f\n", i, wall_height);
		//ft_print_texture(cub, dda_algorithm(cub->player, &cub->ray[i], cub->map));
		i++;
	}*/
	ft_put_img2(&cub->sheet, DEEP_PINK, cub->ray[450].impact.y * 10, cub->ray[450].impact.x * 10);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
	return (0);
}
