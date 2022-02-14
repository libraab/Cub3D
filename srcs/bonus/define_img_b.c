/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_img_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:22:53 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 17:18:51 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	get_minimap_images(t_data *cub)
{
	get_image(cub, &cub->mini_wall, "tex/map/blue.xpm");
	get_image(cub, &cub->frame, "tex/map/yellow.xpm");
	get_image(cub, &cub->mini_player, "tex/map/red.xpm");
	get_image(cub, &cub->mini_door, "tex/map/pink.xpm");
	get_image(cub, &cub->door, "tex/door.xpm");
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
