/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:25:35 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 04:25:36 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	stock_map(t_data *cub, int fd)
{
	int		i;
	int		ret;
	char	*line;

	i = 0;
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ft_is_direction(line[0]) || line[0] == 'F' || line[0] == 'C'
			|| line[0] == '\n' || line[0] == '\0')
		{
			free (line);
			continue ;
		}
		cub->map.map[i++] = ft_strdup(line);
		free (line);
	}
	if (i == 0)
		ft_error(7);
	cub->map.map[i] = ft_calloc(sizeof(char), get_map_width(cub->map.map));
}

void	ft_get_map(t_data *cub, char *file)
{
	int		fd;

	cub->map.map = ft_calloc(sizeof(char *), ft_get_height(file) + 1);
	if (!cub->map.map)
		return ;
	fd = open(file, O_RDONLY);
	stock_map(cub, fd);
	fill_blanks(cub->map.map);
	ft_valid_chars(cub);
	ft_valid_walls(cub);
	close (fd);
}

void	get_wall_textures(t_data *cub, char **texfiles, t_walls *walls)
{
	int	i;

	i = 0;
	while (texfiles[i])
	{
		if (texfiles[i][0] == 'N')
			north_wall_texture(cub, texfiles[i], walls);
		else if (texfiles[i][0] == 'S')
			south_wall_texture(cub, texfiles[i], walls);
		else if (texfiles[i][0] == 'E')
			east_wall_texture(cub, texfiles[i], walls);
		else if (texfiles[i][0] == 'W')
			west_wall_texture(cub, texfiles[i], walls);
		i++;
	}
}

void	stock_texture(t_data *cub, int fd)
{
	int		i;
	int		ret;
	char	*line;

	i = 0;
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ft_end_of_texture(line))
		{
			free (line);
			break ;
		}
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'E'
			|| line[0] == 'W' || line[0] == 'F' || line[0] == 'C')
			cub->tex[i++] = ft_strtrim(ft_strdup(line), " ");
		free (line);
	}
	cub->tex[i] = NULL;
}

void	ft_get_texture(t_data *cub, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	cub->tex = ft_calloc(sizeof(char *), 7);
	if (!cub->tex)
		return ;
	stock_texture(cub, fd);
	ft_check_double_texture(cub, -1, 0);
	get_wall_textures(cub, cub->tex, &cub->walls);
}
