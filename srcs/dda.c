#include "../headers/cub3d.h"

int	dda_algorithm(t_player player, t_ray *ray, t_map map)
{
	int		wall_hit;

	ray->travelled_on_y = distance_to_x_axis(player.position, ray->direction);
	ray->travelled_on_x = distance_to_y_axis(player.position, ray->direction);
	map.x = (int)player.position.x;
	map.y = (int)player.position.y;
	/*if (ray->direction.y == 1 || ray->direction.y == -1)
			wall_hit = ray_ver_wall(map_coord, ray->direction, map);
	else
			wall_hit = ray_hor_wall(map_coord, ray->direction, map);*/
	wall_hit = no_wall;
	while (wall_hit == no_wall)
	{
		if (ray->travelled_on_x < ray->travelled_on_y)
		{
			ray->travelled_on_x += ray->step_x;
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
			if (ray->direction.y > 0)
			{
				map.y += 1;
				if (map.map[map.y][map.x] == '1')
				wall_hit = wall_below;
			}
			else
			{
				map.y -= 1;
				if (map.map[map.y][map.x] == '1')
					wall_hit = wall_above;
			}
		}
	}
	printf("wall %d hit at coordinates %d, %d\n", wall_hit, map.y, map.x);
	return (wall_hit);
}

int	start_dda(t_data *cub)
{
	// dda_algorithm(cub->player, &cub->ray[450], cub->map);
	// mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
	int	i;
	//printf("player position: %f, %f   ray 450 step: %f, %f   ray 450 direction: %f, %f\n", cub->player.position.x, cub->player.position.y, cub->ray[450].step_x, cub->ray[450].step_y, cub->ray[450].direction.x, cub->ray[450].direction.y);
	//dda_algorithm(cub->player, &cub->ray[450], cub->map);
	i = 0;
	while (i < WIN_WIDTH)
	{
		ft_print_texture(cub, dda_algorithm(cub->player, &cub->ray[i], cub->map));
		i++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
	return (0);
}
