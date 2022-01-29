/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:10:46 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/28 20:04:23 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	ft_is_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	ft_tablen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_tabwidth(char **str)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	width = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (j > width)
				width = j;
			j++;
		}
		i++;
	}
	return (width);
}
