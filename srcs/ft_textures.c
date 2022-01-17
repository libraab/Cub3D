/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:41:27 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/17 16:12:34 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	ft_skip_spaces(char *str, int j, int reverse)
{
	if (reverse)
	{
		while (j >= 0 && str[j] == ' ')
			j--;
		return (j);
	}
	else
	{
		while (*str && str[j] == ' ')
			j++;
	}
	return (j);
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

void	ft_check_file(char *str, int j)
{
	int	fd;
	int	i;

	i = ft_strlen(str);
	if (str[--i] == ' ')
		i = ft_skip_spaces(str, j, 1);
	if (str[i] != 'm' || str[i - 1] != 'p'
		|| str[i - 2] != 'x' || str[i - 3] != '.')
		ft_error(1);
	j = ft_skip_spaces(str, j, 0);
	fd = open(&str[j], O_DIRECTORY);
	if (fd != -1)
		ft_error(2);
	fd = open(&str[j], O_RDONLY);
	if (fd < 0)
		ft_error(7);
}

void	ft_check_fc(char **tb)
{
	int	i;
	int	j;

	i = 3;
	while (tb[++i])
	{
		j = -1;
		while (tb[i][++j])
		{
			j = ft_skip_spaces(tb[i], j, 0);
			if ((tb[i][j] != 'F' && tb[i][j] != 'C') || (tb[i][j + 1] != ' '))
				ft_error(8);
			if ((tb[i][j] == 'F' || tb[i][j] == 'C') && (tb[i][j + 1] == ' '))
				ft_check_digits(tb[i], j + 2);
			break ;
		}		
	}
}

void	ft_valid_texture_file(t_data *cub, int i, int j)
{
	while (++i < 4)
	{
		j = -1;
		while (cub->tex[i][++j])
		{
			j = ft_skip_spaces(cub->tex[i], j, 0);
			if (cub->tex[i][j] != 'N' && cub->tex[i][j] != 'S'
				&& cub->tex[i][j] != 'E' && cub->tex[i][j] != 'W')
				ft_error(8);
			if ((cub->tex[i][j] == 'N' || cub->tex[i][j] == 'S')
				&& (cub->tex[i][j + 1] != 'O' || cub->tex[i][j + 2] != ' '))
				ft_error(8);
			else if (cub->tex[i][j] == 'E'
				&& (cub->tex[i][j + 1] != 'A' || cub->tex[i][j + 2] != ' '))
				ft_error(8);
			else if (cub->tex[i][j] == 'W'
				&& (cub->tex[i][j + 1] != 'E' || cub->tex[i][j + 2] != ' '))
				ft_error(8);
			ft_check_file(cub->tex[i], j + 3);
			break ;
		}
	}
	ft_check_fc(cub->tex);
}
