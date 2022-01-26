/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:27:01 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/26 15:24:59 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void ft_draw_frame(t_data *cub)
{
	int	i;
	int	j;

	i = -1;
	while(++i < 20)
	{
		ft_put_img(&cub->sheet, &cub->frame, i * 10, 0);
		ft_put_img(&cub->sheet, &cub->frame, i * 10, 150);
	}
	j = -1;
	while(++j < 15)
	{
		ft_put_img(&cub->sheet, &cub->frame, 0, j * 10);
		ft_put_img(&cub->sheet, &cub->frame, 190, j * 10);
	}
}

void    ft_draw_minimap(t_data *cub)
{
    int x;
    int y;

    y = -1;
    
    while(cub->map[++y])
    {
        x = -1;
        while(cub->map[y][++x])
        {
            if(cub->map[y][x] == '1')
                ft_put_img(&cub->sheet, &cub->wall, x * 10, y * 10);
            if(cub->map[y][x] == 'N' || cub->map[y][x] == 'S' || cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
                ft_put_img(&cub->sheet, &cub->player.img, x * 10, y * 10);
        }
    }
	ft_draw_frame(cub);
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0); 
}
