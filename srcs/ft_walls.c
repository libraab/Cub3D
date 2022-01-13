/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:47:15 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/13 17:42:39 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	ft_north_wall(char **map, int i, int j)
{
	while (map[i][j] && i-- >= 0)
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
	}
	return (0);
}

int	ft_south_wall(char **map, int i, int j)
{
	while (map[i++][j])
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
	}	
	return (0);
}

int	ft_east_wall(char **map, int i, int j)
{
	while (map[i][j] && j-- >= 0)
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
	}
	return (0);
}

int	ft_west_wall(char **map, int i, int j)
{
	while (map[i][j++])
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
	}	
	return (0);
}
