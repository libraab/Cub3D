#include "../../headers/cub3d.h"

void	north_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	int		fd;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	walls->north1.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, \
			&walls->north1.width, &walls->north1.height);
	walls->north1.info.addr = mlx_get_data_addr(walls->north1.img, \
			&walls->north1.info.bits_per_pixel, &walls->north1.info.line_len, \
			&walls->north1.info.endian);
	opposite_side = ft_strjoin(texture_name, "2");
	fd = open(opposite_side, O_RDONLY);
	if (fd < 0)
		walls->north2.img = walls->north1.img;
	else
	{
		walls->north2.img = mlx_xpm_file_to_image(cub->mlx_ptr, opposite_side, \
				&walls->north2.width, &walls->north2.height);
	walls->north2.info.addr = mlx_get_data_addr(walls->north2.img, \
			&walls->north2.info.bits_per_pixel, &walls->north2.info.line_len, \
			&walls->north2.info.endian);
	}
	close(fd);
	free(texture_name);
	free(opposite_side);
}

void	south_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	int		fd;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	walls->south1.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, \
			&walls->south1.width, &walls->south1.height);
	walls->south1.info.addr = mlx_get_data_addr(walls->south1.img, \
			&walls->south1.info.bits_per_pixel, &walls->south1.info.line_len, \
			&walls->south1.info.endian);
	opposite_side = ft_strjoin(texture_name, "2");
	fd = open(opposite_side, O_RDONLY);
	if (fd < 0)
		walls->south2.img = walls->south1.img;
	else
	{
		walls->south2.img = mlx_xpm_file_to_image(cub->mlx_ptr, opposite_side,  \
				&walls->south2.width, &walls->south2.height);
	walls->south2.info.addr = mlx_get_data_addr(walls->south2.img, \
			&walls->south2.info.bits_per_pixel, &walls->south2.info.line_len, \
			&walls->south2.info.endian);
	}
	close(fd);
	free(opposite_side);
	free(texture_name);
}

void	east_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	char	*tmp;
	int		fd;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	walls->east1.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, \
			&walls->east1.width, &walls->east1.height);
	walls->east1.info.addr = mlx_get_data_addr(walls->east1.img, \
			&walls->east1.info.bits_per_pixel, &walls->east1.info.line_len, \
			&walls->east1.info.endian);
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
	{
		walls->east2.img = mlx_xpm_file_to_image(cub->mlx_ptr, opposite_side, \
				&walls->east2.width, &walls->east2.height);
	walls->east2.info.addr = mlx_get_data_addr(walls->east2.img, \
			&walls->east2.info.bits_per_pixel, &walls->east2.info.line_len, \
			&walls->east2.info.endian);
	}
	close(fd);
	free(opposite_side);
}

void	west_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	char	*opposite_side;
	int		fd;

	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	walls->west1.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, \
			&walls->west1.width, &walls->west1.height);
	walls->west1.info.addr = mlx_get_data_addr(walls->west1.img, \
			&walls->west1.info.bits_per_pixel, &walls->west1.info.line_len, \
			&walls->west1.info.endian);
	opposite_side = ft_strjoin(texture_name, "2");
	fd = open(opposite_side, O_RDONLY);
	if (fd < 0)
		walls->west2 = walls->west1;
	else
	{
		walls->west2.img = mlx_xpm_file_to_image(cub->mlx_ptr, opposite_side, \
				&walls->west2.width, &walls->west2.height);
	walls->west2.info.addr = mlx_get_data_addr(walls->west2.img, \
			&walls->west2.info.bits_per_pixel, &walls->west2.info.line_len, \
			&walls->west2.info.endian);
	}
	close(fd);
	free(texture_name);
	free(opposite_side);
}
