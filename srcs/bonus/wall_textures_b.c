/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:24:14 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 15:53:31 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	get_image(t_data *cub, t_img *image, char *texture_name)
{
	image->img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, \
			&image->width, &image->height);
	image->info.addr = mlx_get_data_addr(image->img, \
			&image->info.bits_per_pixel, &image->info.line_len, \
			&image->info.endian);
}

void	north_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	int		fd;
	char	*tmp;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	get_image(cub, &walls->north1, texture_name);
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
		get_image(cub, &walls->north2, opposite_side);
	close(fd);
	free(opposite_side);
}

void	south_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	int		fd;
	char	*tmp;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	get_image(cub, &walls->south1, texture_name);
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
		get_image(cub, &walls->south2, opposite_side);
	close(fd);
	free(opposite_side);
}

void	east_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	char	*tmp;
	int		fd;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	get_image(cub, &walls->east1, texture_name);
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
		get_image(cub, &walls->east2, opposite_side);
	close(fd);
	free(opposite_side);
}

void	west_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	int		fd;
	char	*tmp;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	get_image(cub, &walls->west1, texture_name);
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
		get_image(cub, &walls->west2, opposite_side);
	close(fd);
	free(opposite_side);
}
