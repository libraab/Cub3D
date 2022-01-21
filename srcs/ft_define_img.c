/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:24:24 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/21 16:07:49 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_define_img(t_data *cub)
{
	cub->wall_north.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/minimap/wall_north.xpm", &cub->wall_north.width, &cub->wall_north.height);
	cub->wall_south.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/minimap/wall_south.xpm", &cub->wall_south.width, &cub->wall_south.height);
	cub->wall_east.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/minimap/wall_east.xpm", &cub->wall_east.width, &cub->wall_east.height);
	cub->wall_west.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/minimap/wall_west.xpm", &cub->wall_west.width, &cub->wall_west.height);
	cub->player.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/minimap/player.xpm", &cub->player.width, &cub->player.height);
}

static void	ft_pixel_put(t_info *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + y * data->line_len + x * (data->bits_per_pixel / 8);
	if (color > 0)
		*(unsigned int *) dst = color;
}

static unsigned int	ft_pixel_get(t_info *data, int x, int y)
{
	return (*(unsigned int *)(data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8))));
}

void	ft_put_img(t_img *dest, t_img *src, int x, int y)
{
	t_info	img_src;
	t_info	img_dst;
	int		xx;
	int		yy;

	img_src.addr = mlx_get_data_addr(src->img, &img_src.bits_per_pixel, &img_src.line_len, &img_src.endian);
	img_dst.addr = mlx_get_data_addr(dest->img, &img_dst.bits_per_pixel, &img_dst.line_len, &img_dst.endian);
	yy = -1;
	while (++yy < src->height)
	{
		xx = -1;
		while (++xx < src->width)
			ft_pixel_put(&img_dst, xx + x, yy + y, ft_pixel_get(&img_src, xx, yy));
	}
}
