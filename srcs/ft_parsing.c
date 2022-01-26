/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:17:02 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/25 22:47:02 by bleotard         ###   ########.fr       */
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

void	ft_check_double_texture(t_data *cub, int i, int j, int e)
{
	int	n;
	int	s;
	int	w;
	(void)j;

	n = 0;
	s = 0;
	w = 0;
	while (cub->tex[++i])
	{
		if (cub->tex[i][0] == 'N' && cub->tex[i][1] == 'O')
			n++;
		else if (cub->tex[i][0] == 'S' && cub->tex[i][1] == 'O')
			s++;
		else if (cub->tex[i][0] == 'E' && cub->tex[i][1] == 'A')
			e++;
		else if (cub->tex[i][0] == 'W' && cub->tex[i][1] == 'E')
			w++;
	}
	if (i != 6 || n != 1 || s != 1 || w != 1 || e != 1)
		ft_error(8);
	ft_valid_texture(cub, -1, -1);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int		get_surface(char *surface)
{
	char	**tab;
	int		colour;

	tab = ft_split(surface, ',');
	colour = create_rgb(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]));
	ft_free_double(tab);
	return (colour);
}

void	ft_check_digits(char *str, int j)
{
	char	**tab;
	int		i;

	i = -1;
	tab = ft_split(&str[j], ',');
	while (tab[++i])
	{
		if (ft_atoi(tab[i]) < 0 || ft_atoi(tab[i]) > 255)
			ft_error(8);
	}
	if (i > 3)
		ft_error(8);
	ft_free_double(tab);
}

void	ft_parse(t_data *cub)
{
	ft_valid_chars(cub);
	ft_valid_walls(cub);
}
