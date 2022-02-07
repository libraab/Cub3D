#include "../headers/cub3d.h"

void	dda_algorithm(t_player player, t_ray *ray, char **map)
{
	int		wall_hit;
	float	travelled_on_y;
	float	travelled_on_x;
	int		coord_y;
	int		coord_x;

	travelled_on_y = distance_to_x_axis(player.position, ray->direction);
	travelled_on_x = distance_to_y_axis(player.position, ray->direction);
	coord_x = (int)player.position.x;
	coord_y = (int)player.position.y;
	/*if (ray->direction.y == 1 || ray->direction.y == -1)
			wall_hit = ray_ver_wall(map_coord, ray->direction, map);
	else
			wall_hit = ray_hor_wall(map_coord, ray->direction, map);*/
	wall_hit = no_wall;
	while (wall_hit == no_wall)
	{
		if (travelled_on_x < travelled_on_y)
		{
			travelled_on_x += ray->step_x;
			if (ray->direction.x > 0)
			{
				coord_x += 1;
				if (map[coord_y][coord_x] == '1')
					wall_hit = wall_left;
			}
			else
			{
				coord_x -= 1;
				if (map[coord_y][coord_x] == '1')
					wall_hit = wall_right;
			}
		}
		else
		{
			travelled_on_y += ray->step_y;
			if (ray->direction.y > 0)
			{
				coord_y += 1;
				if (map[coord_y][coord_x] == '1')
				wall_hit = wall_below;
			}
			else
			{
				coord_y -= 1;
				if (map[coord_y][coord_x] == '1')
					wall_hit = wall_above;
			}
		}
	}
	printf("wall %d hit at coordinates %d, %d\n", wall_hit, coord_y, coord_x);
}

int	start_dda(t_data *cub)
{
	int	i;
//	printf("player position: %f, %f   ray 450 step: %f, %f   ray 450 direction: %f, %f\n", cub->player.position.x, cub->player.position.y, cub->ray[450].step_x, cub->ray[450].step_y, cub->ray[450].direction.x, cub->ray[450].direction.y);
//		dda_algorithm(cub->player, &cub->ray[450], cub->map);
	i = 0;
	while (i < WIN_WIDTH)
	{
		dda_algorithm(cub->player, &cub->ray[i], cub->map.map);
		i++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
	return (0);
}
