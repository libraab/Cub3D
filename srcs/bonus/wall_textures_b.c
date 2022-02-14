/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:24:14 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 04:24:15 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	ft_define_wall(t_data *cub, char *texture_name, t_walls *walls)
{
	walls->north1.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, \
			&walls->north1.width, &walls->north1.height);
	walls->north1.info.addr = mlx_get_data_addr(walls->north1.img, \
			&walls->north1.info.bits_per_pixel, &walls->north1.info.line_len, \
			&walls->north1.info.endian);
	walls->south1.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, \
			&walls->south1.width, &walls->south1.height);
	walls->south1.info.addr = mlx_get_data_addr(walls->south1.img, \
			&walls->south1.info.bits_per_pixel, &walls->south1.info.line_len, \
			&walls->south1.info.endian);
	walls->east1.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, \
			&walls->east1.width, &walls->east1.height);
	walls->east1.info.addr = mlx_get_data_addr(walls->east1.img, \
			&walls->east1.info.bits_per_pixel, &walls->east1.info.line_len, \
			&walls->east1.info.endian);
	walls->west1.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, \
			&walls->west1.width, &walls->west1.height);
	walls->west1.info.addr = mlx_get_data_addr(walls->west1.img, \
			&walls->west1.info.bits_per_pixel, &walls->west1.info.line_len, \
			&walls->west1.info.endian);
}

void	north_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	int		fd;
	char	*tmp;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	ft_define_wall(cub, texture_name, walls);
	opposite_side = ft_strtrim(texture_name, ".xpm");
	tmp = ft_strjoin(opposite_side, "2");
	free(opposite_side);
	opposite_side = tmp;
	tmp = ft_strjoin(opposite_side, ".xpm");
	free(opposite_side);
	opposite_side = tmp;
	fd = open(opposite_side, O_RDONLY);
	if (fd < 0)
		walls->north2 = walls->north1;
	else
		ft_define_wall2(cub, walls, opposite_side);
	close(fd);
	free(opposite_side);
}

void	south_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	int		fd;
	char	*tmp;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	ft_define_wall(cub, texture_name, walls);
	opposite_side = ft_strtrim(texture_name, ".xpm");
	tmp = ft_strjoin(opposite_side, "2");
	free(opposite_side);
	opposite_side = tmp;
	tmp = ft_strjoin(opposite_side, ".xpm");
	free(opposite_side);
	opposite_side = tmp;
	fd = open(opposite_side, O_RDONLY);
	if (fd < 0)
		walls->south2 = walls->south1;
	else
		ft_define_wall2(cub, walls, opposite_side);
	close(fd);
	free(opposite_side);
}

void	east_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	char	*tmp;
	int		fd;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	ft_define_wall(cub, texture_name, walls);
	opposite_side = ft_strtrim(texture_name, ".xpm");
	tmp = ft_strjoin(opposite_side, "2");
	free(opposite_side);
	opposite_side = tmp;
	tmp = ft_strjoin(opposite_side, ".xpm");
	free(opposite_side);
	opposite_side = tmp;
	fd = open(opposite_side, O_RDONLY);
	if (fd < 0)
		walls->east2 = walls->east1;
	else
		ft_define_wall2(cub, walls, opposite_side);
	close(fd);
	free(opposite_side);
}

void	west_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	int		fd;
	char	*tmp;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	ft_define_wall(cub, texture_name, walls);
	opposite_side = ft_strtrim(texture_name, ".xpm");
	tmp = ft_strjoin(opposite_side, "2");
	free(opposite_side);
	opposite_side = tmp;
	tmp = ft_strjoin(opposite_side, ".xpm");
	free(opposite_side);
	opposite_side = tmp;
	fd = open(opposite_side, O_RDONLY);
	if (fd < 0)
		walls->west2 = walls->west1;
	else
		ft_define_wall2(cub, walls, opposite_side);
	close(fd);
	free(opposite_side);
}
