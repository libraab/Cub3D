/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:27:01 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/27 17:28:34 by abouhlel         ###   ########.fr       */
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
		ft_put_img(&cub->sheet, &cub->frame, i * 10, 0);
		ft_put_img(&cub->sheet, &cub->frame, i * 10, 150);
	}
	j = -1;
	while (++j < 15)
	{
		ft_put_img(&cub->sheet, &cub->frame, 0, j * 10);
		ft_put_img(&cub->sheet, &cub->frame, 190, j * 10);
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
				ft_put_img(&cub->sheet, &cub->wall, x * 10, y * 10);
			if (ft_is_direction(cub->map[y][x]))
				ft_put_img(&cub->sheet, &cub->player.img, x * 10, y * 10);
		}
	}
}
