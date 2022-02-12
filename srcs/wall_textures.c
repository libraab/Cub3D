#include "../headers/cub3d.h"

void	north_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	walls->north.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name,
			&walls->north.width, &walls->north.height);
	walls->north.info.addr = mlx_get_data_addr(walls->north.img,
			&walls->north.info.bits_per_pixel, &walls->north.info.line_len,
			&walls->north.info.endian);
	free(texture_name);
}

void	south_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	walls->south.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name,
			&walls->south.width, &walls->south.height);
	walls->south.info.addr = mlx_get_data_addr(walls->south.img,
			&walls->south.info.bits_per_pixel, &walls->south.info.line_len,
			&walls->south.info.endian);
	free(texture_name);
}

void	east_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	walls->east.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name,
			&walls->east.width, &walls->east.height);
	walls->east.info.addr = mlx_get_data_addr(walls->east.img,
			&walls->east.info.bits_per_pixel, &walls->east.info.line_len,
			&walls->east.info.endian);
	free(texture_name);
}

void	west_wall_texture(t_data *cub, char *texture_name, t_walls *walls)
{
	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	walls->west.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name,
			&walls->west.width, &walls->west.height);
	walls->west.info.addr = mlx_get_data_addr(walls->west.img,
			&walls->west.info.bits_per_pixel, &walls->west.info.line_len,
			&walls->west.info.endian);
	free(texture_name);
}
