/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:27:01 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/26 11:23:53 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void ft_draw_frame(t_data *cub)
{
	int	i;
	int	j;

	i = 49;
	while(++i < 250)
	{
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, i, 50, RED);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, i, 51, RED);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, i, 199, RED);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, i, 200, RED);
		if (i < 201)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 50, i, RED);
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 51, i, RED);
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 250, i, RED);
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 251, i, RED);
		}
		j = 51;
		while(++j < 199)
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, i, j, GOLD);
	}
}

void    ft_draw_minimap(t_data *cub)
{
    int x;
    int y;

    y = -1;
    
    ft_draw_frame(cub);
    while(cub->map[++y])
    {
        x = -1;
        while(cub->map[y][++x])
        {
            if(cub->map[y][x] == '1')
                ft_put_img(&cub->sheet, &cub->wall_north, x * 10, y * 10);
            if(cub->map[y][x] == 'N' || cub->map[y][x] == 'S' || cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
                ft_put_img(&cub->sheet, &cub->player.img, x * 10, y * 10);
        }
    }
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0); 
}
