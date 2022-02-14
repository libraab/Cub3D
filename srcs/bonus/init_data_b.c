/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:23:11 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 04:23:12 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

t_player	init_player(char **map)
{
	int			i;
	int			j;
	t_player	player;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' \
					|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				player.pos.y = i + 0.5;
				player.pos.x = j + 0.5;
				player.direction = starting_direction(map[i][j]);
			}
			j++;
		}
		i++;
	}
	return (player);
}

void	ft_init_data(t_data *cub, char **av)
{
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	cub->sheet.img = mlx_new_image(cub->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	cub->sheet.info.addr = mlx_get_data_addr(cub->sheet.img,
			&cub->sheet.info.bits_per_pixel, &cub->sheet.info.line_len,
			&cub->sheet.info.endian);
	ft_get_map(cub, av[1]);
	ft_get_texture(cub, av[1]);
	cub->map_width = get_map_width(cub->map.map);
	cub->map_height = get_map_height(cub->map.map);
	cub->player = init_player(cub->map.map);
	cub->mouse_x = 750;
	get_minimap_images(cub);
	ft_draw_minimap(cub);
	cast_ray(cub->ray, cub->player);
	start_dda(cub);
}
