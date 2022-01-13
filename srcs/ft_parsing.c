/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:17:02 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/13 15:09:09 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_valid_file(t_data *cub, char *file)
{
	int	i;
	int	fd;

	i = ft_strlen(file) - 1;
	if (file[i] != 'b' && file[i - 1] != 'u'
		&& file[i - 2] != 'c'
		&& file[i - 3] != '.')
		ft_error(cub, 1);
	fd = open(file, O_DIRECTORY);
	if (fd != -1)
		ft_error(cub, 2);
	close (fd);
}

void	ft_valid_chars(t_data *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] != ' ' && cub->map[i][j] != '0'
				&& cub->map[i][j] != '1' && cub->map[i][j] != 'E'
				&& cub->map[i][j] != 'N' && cub->map[i][j] != 'S'
				&& cub->map[i][j] != 'W')
				ft_error(cub, 3);
		}
	}
}

void	ft_one_direction(t_data *cub)
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
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
				count++;
		}
	}
	if (count == 0)
		ft_error(cub, 4);
	if (count != 1)
		ft_error(cub, 5);
}

int	ft_check_error(t_data *cub, char **av)
{
	ft_valid_file(cub, av[1]);
	ft_stock_map(cub, av[1]);
	ft_valid_chars(cub);
	ft_one_direction(cub);
	//ft_valid_walls(cub);
	return (1);
}
