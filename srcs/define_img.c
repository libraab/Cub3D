/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:24:24 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/30 19:09:18 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_define_img(t_data *cub)
{
	cub->wall.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/minimap/blue.xpm", &cub->wall.width, &cub->wall.height);
	cub->frame.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/minimap/yellow.xpm", &cub->frame.width, &cub->frame.height);
	cub->player.img.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/minimap/red.xpm", &cub->player.img.width, &cub->player.img.height);
}

void	ft_pixel_put(t_info *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + y * data->line_len + x * (data->bits_per_pixel / 8);
	if (color > 0)
		*(unsigned int *) dst = color;
}

unsigned int	ft_pixel_get(t_info *data, int x, int y)
{
	return (*(unsigned int *)(data->addr + (y * data->line_len
			+ x * (data->bits_per_pixel / 8))));
}

void	ft_put_img(t_img *dest, t_img *src, float x, float y)
{
	t_info	img_src;
	t_info	img_dst;
	int		xx;
	int		yy;

	img_src.addr = mlx_get_data_addr(src->img, &img_src.bits_per_pixel,
			&img_src.line_len, &img_src.endian);
	img_dst.addr = mlx_get_data_addr(dest->img, &img_dst.bits_per_pixel,
			&img_dst.line_len, &img_dst.endian);
	yy = -1;
	while (++yy < src->height)
	{
		xx = -1;
		while (++xx < src->width)
			ft_pixel_put(&img_dst, xx + x, yy + y, ft_pixel_get(&img_src, xx, yy));
	}
}

void	ft_put_img2(t_img *dest, int color, int x, int y)
{
	t_info	img_dest;

	img_dest.addr = mlx_get_data_addr(dest->img, &img_dest.bits_per_pixel,
			&img_dest.line_len, &img_dest.endian);
	ft_pixel_put(&img_dest, y, x, color);
}
