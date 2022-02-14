/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:25:25 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 15:39:57 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	print_north_wall(t_data *cub, int wall_height, \
		int column, float ratio_x)
{
	float	wall_ratio;
	float	wall_start;
	float	wall_end;
	int		i;

	wall_end = WIN_HEIGHT / 2 + wall_height / 2;
	wall_start = WIN_HEIGHT / 2 - wall_height / 2;
	i = wall_start;
	while (i < wall_end && i < WIN_HEIGHT)
	{
		wall_ratio = (i - wall_start) / wall_height;
		if (i > 0 && (int)cub->ray[column].impact.x <= cub->map_width / 2)
		{
			ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.north2.info, \
						(int)(ratio_x * cub->walls.north2.width), \
						wall_ratio * cub->walls.north2.height), i, column);
		}
		else if (i > 0)
		{
			ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.north1.info, \
						(int)(ratio_x * cub->walls.north1.width), \
						wall_ratio * cub->walls.north1.height), i, column);
		}
		i++;
	}
}

void	print_south_wall(t_data *cub, int wall_height, \
		int column, float ratio_x)
{
	float	wall_ratio;
	float	wall_start;
	float	wall_end;
	int		i;

	wall_end = WIN_HEIGHT / 2 + wall_height / 2;
	wall_start = WIN_HEIGHT / 2 - wall_height / 2;
	i = wall_start;
	while (i < wall_end && i < WIN_HEIGHT)
	{
		wall_ratio = (i - wall_start) / wall_height;
		if (i > 0 && (int)cub->ray[column].impact.x <= cub->map_width / 2)
		{
			ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.south2.info, \
						(int)(ratio_x * cub->walls.south2.width), \
						wall_ratio * cub->walls.south2.height), i, column);
		}
		else if (i > 0)
		{
			ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.south1.info, \
						(int)(ratio_x * cub->walls.south1.width), \
						wall_ratio * cub->walls.south1.height), i, column);
		}
		i++;
	}
}

void	print_east_wall(t_data *cub, int wall_height, int column, float ratio_y)
{
	float	wall_ratio;
	float	wall_start;
	float	wall_end;
	int		i;

	wall_end = WIN_HEIGHT / 2 + wall_height / 2;
	wall_start = WIN_HEIGHT / 2 - wall_height / 2;
	i = wall_start;
	while (i < wall_end && i < WIN_HEIGHT)
	{
		wall_ratio = (i - wall_start) / wall_height;
		if (i > 0 && (int)cub->ray[column].impact.x <= cub->map_width / 2)
		{
			ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.east2.info, \
						(int)(ratio_y * cub->walls.east2.width), \
						wall_ratio * cub->walls.east2.height), i, column);
		}
		else if (i > 0)
		{
			ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.east1.info, \
						(int)(ratio_y * cub->walls.east1.width), \
						wall_ratio * cub->walls.east1.height), i, column);
		}
		i++;
	}
}

void	print_west_wall(t_data *cub, int wall_height, int column, float ratio_y)
{
	float	wall_ratio;
	float	wall_start;
	float	wall_end;
	int		i;

	wall_end = WIN_HEIGHT / 2 + wall_height / 2;
	wall_start = WIN_HEIGHT / 2 - wall_height / 2;
	i = wall_start;
	while (i < wall_end && i < WIN_HEIGHT)
	{
		wall_ratio = (i - wall_start) / wall_height;
		if (i > 0 && (int)cub->ray[column].impact.x <= cub->map_width / 2)
		{
			ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.west2.info, \
						(int)(ratio_y * cub->walls.west2.width), \
						wall_ratio * cub->walls.west2.height), i, column);
		}
		else if (i > 0)
		{
			ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.west1.info, \
						(int)(ratio_y * cub->walls.west1.width), \
						wall_ratio * cub->walls.west1.height), i, column);
		}
		i++;
	}
}

void	ft_print_texture(t_data *cub, int wall_height, \
		int wall_type, int column)
{
	float	ratio_x;
	float	ratio_y;

	cub->map.x = (int)cub->ray[column].impact.x;
	cub->map.y = (int)cub->ray[column].impact.y;
	ratio_x = cub->ray[column].impact.x - cub->map.x;
	ratio_y = cub->ray[column].impact.y - cub->map.y;
	if (wall_type == north_wall)
		print_north_wall(cub, wall_height, column, (1 - ratio_x));
	if (wall_type == south_wall)
		print_south_wall(cub, wall_height, column, ratio_x);
	if (wall_type == west_wall)
		print_west_wall(cub, wall_height, column, (1 - ratio_y));
	if (wall_type == east_wall)
		print_east_wall(cub, wall_height, column, ratio_y);
}
