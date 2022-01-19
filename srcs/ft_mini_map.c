/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:27:01 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/19 14:51:07 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

unsigned int	mlx_get_pixel_img(const t_img *img, int x, int y)
{
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	return (*(unsigned int *)(img->info.addr + (y * img->info.line_len + x * (img->info.bits_per_pixel / 8))));
}

void	mlx_put_pixel_to_img(t_img *dest, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= dest->width || y < 0 || y >= dest->height)
		return ;
	if (color == 0xFF000000)
		return ;
	dst = dest->info.addr + (y * dest->info.line_len + x * (dest->info.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mlx_put_img_to_img(t_img *dest, const t_img *src, int x, int y)
{
	int		current_x;
	int		current_y;

	current_y = 0;
	current_x = 0;
	while (current_y < src->height)
	{
		current_x = 0;
		while (current_x < src->width)
		{
			mlx_put_pixel_to_img(dest, current_x + x, current_y + y, mlx_get_pixel_img(src, current_x, current_y));
			current_x++;
		}
		current_y++;
	}
}

void	create_img(t_img *img, void *mlx_img)
{
	img->img = mlx_img;
	img->info.addr = mlx_get_data_addr(mlx_img, &img->info.bits_per_pixel, &img->info.line_len, &img->info.endian);
}