/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:17:02 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/13 18:19:16 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_valid_chars(t_data *cub)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] != ' ' && cub->map[i][j] != '0'
				&& cub->map[i][j] != '1' && cub->map[i][j] != 'E'
				&& cub->map[i][j] != 'N' && cub->map[i][j] != 'S'
				&& cub->map[i][j] != 'W')
				ft_error(3);
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
				count++;
		}
	}
	if (count == 0)
		ft_error(4);
	if (count != 1)
		ft_error(5);
}

void	ft_valid_walls(t_data *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == '0' && i == 0 && j == 0)
				ft_error(6);
			if (cub->map[i][j] == '0')
			{
				if (!ft_north_wall(cub->map, i, j)
					|| !ft_south_wall(cub->map, i, j)
					|| !ft_east_wall(cub->map, i, j)
					|| !ft_west_wall(cub->map, i, j))
					ft_error(6);
			}
		}
	}
}

void	ft_parse(t_data *cub, char **av)
{
	ft_stock_map(cub, av[1]);
	ft_valid_chars(cub);
	ft_valid_walls(cub);
	printf("let's parse now\n");
}
