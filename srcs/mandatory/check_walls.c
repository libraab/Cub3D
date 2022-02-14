/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:24:26 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 04:24:27 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	ft_north_wall(char **map, int i, int j)
{
	while (i >= 0)
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
		i--;
	}
	return (0);
}

int	ft_south_wall(char **map, int i, int j)
{
	while (map[i][j])
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
		i++;
	}	
	return (0);
}

int	ft_east_wall(char **map, int i, int j)
{
	while (j >= 0)
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
		j--;
	}
	return (0);
}

int	ft_west_wall(char **map, int i, int j)
{
	while (map[i][j])
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
		j++;
	}	
	return (0);
}
