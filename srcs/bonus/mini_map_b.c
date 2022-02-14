/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:23:30 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 04:23:31 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	ft_define_wall2(t_data *cub, t_walls *walls, char *opposite_side)
{
	walls->north2.img = mlx_xpm_file_to_image(cub->mlx_ptr, opposite_side, \
			&walls->north2.width, &walls->north2.height);
	walls->north2.info.addr = mlx_get_data_addr(walls->north2.img, \
			&walls->north2.info.bits_per_pixel, &walls->north2.info.line_len, \
			&walls->north2.info.endian);
	walls->south2.img = mlx_xpm_file_to_image(cub->mlx_ptr, opposite_side,
			&walls->south2.width, &walls->south2.height);
	walls->south2.info.addr = mlx_get_data_addr(walls->south2.img, \
			&walls->south2.info.bits_per_pixel, &walls->south2.info.line_len, \
			&walls->south2.info.endian);
	walls->east2.img = mlx_xpm_file_to_image(cub->mlx_ptr, opposite_side, \
			&walls->east2.width, &walls->east2.height);
	walls->east2.info.addr = mlx_get_data_addr(walls->east2.img, \
			&walls->east2.info.bits_per_pixel, &walls->east2.info.line_len, \
			&walls->east2.info.endian);
	walls->west2.img = mlx_xpm_file_to_image(cub->mlx_ptr, opposite_side, \
			&walls->west2.width, &walls->west2.height);
	walls->west2.info.addr = mlx_get_data_addr(walls->west2.img, \
			&walls->west2.info.bits_per_pixel, &walls->west2.info.line_len, \
			&walls->west2.info.endian);
}

void	fill_minimap_characters(t_data *cub, int *minimap_boundaries, int i)
{
	int	j;
	int	x;

	j = 0;
	x = minimap_boundaries[left];
	while (x <= minimap_boundaries[right] && \
			cub->map.map[minimap_boundaries[up]][x])
	{
		if (minimap_boundaries[up] == (int)cub->player.pos.y && \
				x == (int)cub->player.pos.x)
			cub->minimap[i][j] = 'P';
		else
			cub->minimap[i][j] = cub->map.map[minimap_boundaries[up]][x];
		cub->minimap[i][++j] = '\0';
		x++;
	}
}

void	ft_stock_minimap(t_data *cub, int *minimap_boundaries)
{
	int	i;

	if (cub->minimap != NULL)
		ft_free_double(cub->minimap);
	cub->minimap = ft_calloc(sizeof(char *), 17);
	i = 0;
	while (i < 16)
		cub->minimap[i++] = ft_calloc(sizeof(char), 16);
	i = 0;
	while (minimap_boundaries[up] <= minimap_boundaries[down] && \
			cub->map.map[minimap_boundaries[up]])
	{
		fill_minimap_characters(cub, minimap_boundaries, i++);
		minimap_boundaries[up]++;
	}
}

void	ft_print_minimap(t_data *cub)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cub->minimap[++i])
	{
		j = 0;
		while (cub->minimap[i][j])
		{
			if (cub->minimap[i][j] == '1')
				ft_put_img(&cub->sheet, &cub->mini_wall, 10 + (j * 10),
					10 + (i * 10));
			else if (cub->minimap[i][j] != ' ')
				ft_put_img(&cub->sheet, &cub->frame, 10 + (j * 10),
					10 + (i * 10));
			if (cub->minimap[i][j] == 'P')
				ft_put_img(&cub->sheet, &cub->player.img, 10 + (j * 10),
					10 +(i * 10));
			if (cub->minimap[i][j] == '2')
				ft_put_img(&cub->sheet, &cub->mini_door, 10 + (j * 10),
					10 + (i * 10));
			j++;
		}
	}
}

void	ft_draw_minimap(t_data *cub)
{
	int	minimap_boundaries[4];

	ft_get_minimap_boundaries(cub, &minimap_boundaries[0]);
	ft_stock_minimap(cub, minimap_boundaries);
	ft_print_minimap(cub);
}
