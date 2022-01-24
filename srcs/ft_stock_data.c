/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:29:20 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/24 06:17:39 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_init_img(t_img *img)
{
	img->img = NULL;
	img->width = 0;
	img->height = 0;
}

void	ft_init_data(t_data *cub)
{
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->map = NULL;
	cub->tex = NULL;
	ft_init_img(&cub->wall_north);
	ft_init_img(&cub->wall_south);
	ft_init_img(&cub->wall_east);
	ft_init_img(&cub->wall_west);
	ft_init_img(&cub->mini);
	ft_init_img(&cub->player);
	cub->pos_x = 0;
	cub->pos_y = 0;
}

void	ft_stock_map(t_data *cub, char *file)
{
	int		i;
	int		fd;
	int		ret;
	char	*line;

	i = 0;
	ret = 1;
	fd = open(file, O_RDONLY);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (line[0] == 'N' || line[0] == 'S'
			|| line[0] == 'E' || line[0] == 'W'
			|| line[0] == 'F' || line[0] == 'C'
			|| line[0] == '\n' || line[0] == '\0')
		{
			free (line);
			continue ;
		}
		cub->map[i++] = ft_strdup(line);
		free (line);
	}
	close (fd);
}

void	ft_stock_texture(t_data *cub, char *file)
{
	int		i;
	int		fd;
	int		ret;
	char	*line;

	i = 0;
	ret = 1;
	fd = open(file, O_RDONLY);
	cub->tex = ft_calloc(sizeof(char *), 7);
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
	close (fd);
	ft_check_double_texture(cub, -1, -1, 0);
}
