/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:23:30 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 16:00:28 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

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
				ft_put_img(&cub->sheet, &cub->mini_player, 10 + (j * 10),
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
