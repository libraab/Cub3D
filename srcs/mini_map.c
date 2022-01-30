/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:27:01 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/30 19:25:26 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_update_map(t_data *cub, int x, int y)
{
	int	i;
	int	j;
	
	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (ft_is_direction(cub->map[i][j]))
			{
				cub->map[i + x][j + y] = cub->map[i][j];
				cub->map[i][j] = '0';
				j++;
			}
		}
	}
}

void	ft_draw_frame(t_data *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 20)
	{
		ft_put_img(&cub->sheet, &cub->frame, (float)i * 10, 0.0);
		ft_put_img(&cub->sheet, &cub->frame, (float)i * 10, 150.0);
	}
	j = -1;
	while (++j < 15)
	{
		ft_put_img(&cub->sheet, &cub->frame, 0.0, (float)j * 10);
		ft_put_img(&cub->sheet, &cub->frame, 190.0, (float)j * 10);
	}
}

void	ft_draw_minimap(t_data *cub)
{
	int	x;
	int	y;

	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == '1')
				ft_put_img(&cub->sheet, &cub->wall, (float)x * 10, (float)y * 10);
			else if (x != (int)cub->player.position.x / TILE_SIZE || y != (int)cub->player.position.y / TILE_SIZE)
				ft_put_img(&cub->sheet, &cub->frame, (float)x * 10, (float)y * 10);
			else
				ft_put_img(&cub->sheet, &cub->player.img, (float)x * 10, (float)y * 10);
		   	//ft_put_img2(&cub->sheet, RED, cub->player.position.y / TILE_SIZE * 10, cub->player.position.x / TILE_SIZE * 10);
		}
	}
}
