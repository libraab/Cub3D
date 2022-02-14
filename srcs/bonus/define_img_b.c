/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_img_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:22:53 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 04:22:54 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	get_minimap_images(t_data *cub)
{
	cub->mini_wall.img = mlx_xpm_file_to_image(cub->mlx_ptr, "tex/map/blue.xpm",
			&cub->mini_wall.width, &cub->mini_wall.height);
	cub->mini_wall.info.addr = mlx_get_data_addr(cub->mini_wall.img,
			&cub->mini_wall.info.bits_per_pixel,
			&cub->mini_wall.info.line_len, &cub->mini_wall.info.endian);
	cub->frame.img = mlx_xpm_file_to_image(cub->mlx_ptr, "tex/map/yellow.xpm",
			&cub->frame.width, &cub->frame.height);
	cub->frame.info.addr = mlx_get_data_addr(cub->frame.img,
			&cub->frame.info.bits_per_pixel,
			&cub->frame.info.line_len, &cub->frame.info.endian);
	cub->player.img.img = mlx_xpm_file_to_image(cub->mlx_ptr, "tex/map/red.xpm",
			&cub->player.img.width, &cub->player.img.height);
	cub->player.img.info.addr = mlx_get_data_addr(cub->player.img.img,
			&cub->player.img.info.bits_per_pixel,
			&cub->player.img.info.line_len, &cub->player.img.info.endian);
	cub->mini_door.img = mlx_xpm_file_to_image(cub->mlx_ptr, "tex/map/pink.xpm",
			&cub->mini_door.width, &cub->mini_door.height);
	cub->mini_door.info.addr = mlx_get_data_addr(cub->mini_door.img,
			&cub->mini_door.info.bits_per_pixel,
			&cub->mini_door.info.line_len, &cub->mini_door.info.endian);
	cub->door.img = mlx_xpm_file_to_image(cub->mlx_ptr, "tex/door.xpm",
			&cub->door.width, &cub->door.height);
	cub->door.info.addr = mlx_get_data_addr(cub->door.img,
			&cub->door.info.bits_per_pixel,
			&cub->door.info.line_len, &cub->door.info.endian);
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

void	ft_put_img(t_img *dest, t_img *src, int x, int y)
{
	int		xx;
	int		yy;

	yy = -1;
	while (++yy < src->height)
	{
		xx = -1;
		while (++xx < src->width)
			ft_pixel_put(&dest->info, xx + x, yy + y,
				ft_pixel_get(&src->info, xx, yy));
	}
}

void	ft_put_img2(t_img *dest, int color, int x, int y)
{
	t_info	img_dest;

	img_dest.addr = mlx_get_data_addr(dest->img, &img_dest.bits_per_pixel,
			&img_dest.line_len, &img_dest.endian);
	ft_pixel_put(&img_dest, y, x, color);
}
