/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:50:23 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/26 18:56:07 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	draw_fov(t_ray rays[WIN_WIDTH], t_data *cub, int colour)
{
	t_vector	center;
	int			i;

	center.x = WIN_WIDTH / 2;
	center.y = WIN_HEIGHT / 2;
	i = 0;
	while (i < WIN_WIDTH)
	{
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, center.x + rays[i].direction.x * 200, center.y + rays[i].direction.y * 200, colour);
		i++;
	}
}

void	draw_floor(t_data *cub)
{
	int	i;
	int	j;

	i = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		j = - 1;
		while (++j < WIN_WIDTH)
			ft_put_img2(&cub->sheet, cub->floor, i, j);
		i++;
	}
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
}

void	draw_ceiling(t_data *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT / 2)
	{
		j = 0;
		while (++j < WIN_WIDTH)
			ft_put_img2(&cub->sheet, cub->ceiling, i, j);
		i++;
	}
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
}
