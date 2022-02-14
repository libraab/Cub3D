/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:22:33 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 04:22:34 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	ft_skip_spaces(char *str, int i, int reverse)
{
	int	x;

	if (reverse)
	{
		x = ft_strlen(str);
		while (x >= 0 && str[x] == ' ')
			x--;
		return (x);
	}
	else
	{
		while (*str && str[i] == ' ')
			i++;
	}
	return (i);
}

int	ft_end_of_texture(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\0')
		return (0);
	if (line[i] != ' ' && line[i] != '1'
		&& line[i] != '0' && line[i] != '\n')
		return (0);
	return (1);
}

void	ft_valid_texture_file(char *str)
{
	int	fd;
	int	i;

	i = ft_strlen(str) - 1;
	if (str[i] != 'm' || str[i - 1] != 'p'
		|| str[i - 2] != 'x' || str[i - 3] != '.')
		ft_error(1);
	i = ft_skip_spaces(str, 2, 0);
	fd = open(&str[i], O_DIRECTORY);
	if (fd != -1)
		ft_error(2);
	fd = open(&str[i], O_RDONLY);
	if (fd < 0)
		ft_error(7);
	close (fd);
}

void	ft_check_floor_ceiling(t_data *cub)
{
	if ((cub->tex[4][0] == 'F' && cub->tex[5][0] != 'C')
			|| (cub->tex[4][0] == 'C' && cub->tex[5][0] != 'F'))
		ft_error(8);
	if (cub->tex[4][1] != ' ' || cub->tex[5][1] != ' ')
		ft_error(8);
	ft_check_digits(cub->tex[4]);
	ft_check_digits(cub->tex[5]);
	if (cub->tex[4][0] == 'F')
	{
		cub->floor = get_surface(cub->tex[4]);
		cub->ceiling = get_surface(cub->tex[5]);
	}
	else
	{
		cub->ceiling = get_surface(cub->tex[4]);
		cub->floor = get_surface(cub->tex[5]);
	}
}

void	ft_valid_texture(t_data *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!ft_is_direction(cub->tex[i][0]) || cub->tex[i][2] != ' ')
			ft_error(8);
		if ((cub->tex[i][0] == 'N' || cub->tex[i][0] == 'S')
			&& (cub->tex[i][1] != 'O'))
			ft_error(8);
		else if ((cub->tex[i][0] == 'E' && cub->tex[i][1] != 'A')
				|| (cub->tex[i][0] == 'W' && cub->tex[i][1] != 'E'))
			ft_error(8);
		ft_valid_texture_file(cub->tex[i]);
	}
	ft_check_floor_ceiling(cub);
}
