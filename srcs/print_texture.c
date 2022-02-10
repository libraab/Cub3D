#include "../headers/cub3d.h"

void	init_tex_ns(t_data *cub, char *texture_name, t_walls *walls, int x)
{
	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	if (x == 0)
	{
		walls->north.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name,
				&walls->north.width, &walls->north.height);
		walls->north.info.addr = mlx_get_data_addr(walls->north.img,
				&walls->north.info.bits_per_pixel, &walls->north.info.line_len,
				&walls->north.info.endian);
	}
	if (x == 1)
	{
		walls->south.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name,
				&walls->south.width, &walls->south.height);
		walls->south.info.addr = mlx_get_data_addr(walls->south.img,
				&walls->south.info.bits_per_pixel, &walls->south.info.line_len,
				&walls->south.info.endian);
	}
}

void	init_tex_ew(t_data *cub, char *texture_name, t_walls *walls, int x)
{
	texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
	if (x == 0)
	{
		walls->east.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name,
				&walls->east.width, &walls->east.height);
		walls->east.info.addr = mlx_get_data_addr(walls->east.img,
				&walls->east.info.bits_per_pixel, &walls->east.info.line_len,
				&walls->east.info.endian);
	}
	if (x == 1)
	{
		walls->west.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name,
				&walls->west.width, &walls->west.height);
		walls->west.info.addr = mlx_get_data_addr(walls->west.img,
				&walls->west.info.bits_per_pixel, &walls->west.info.line_len,
				&walls->west.info.endian);
	}
}

void	ft_print_texture(t_data *cub, int wall_height, int wall_type, int column)
{
	//int	texture_column;
	//t_img	texture;
	int		i;
	float	ratio_x;
	float	ratio_y;
	float	wall_ratio;
	float	wall_start;
	float	wall_end;

	cub->map.x = (int)cub->ray[column].impact.x;
	cub->map.y = (int)cub->ray[column].impact.y;
	ratio_x = cub->ray[column].impact.x - cub->map.x;
	ratio_y = cub->ray[column].impact.y - cub->map.y;
	//printf("ratio_x: %f, texture width: %d, printed column: %f\n", ratio_x, cub->walls.north.width, ratio_x * cub->walls.north.width);
	wall_end = WIN_HEIGHT / 2 + wall_height / 2;
	wall_start = WIN_HEIGHT / 2 - wall_height / 2;
	i = wall_start;
	if (wall_type == wall_above)
	{
		while (i < wall_end && i < WIN_HEIGHT)
		{
			wall_ratio = (i - wall_start) / wall_height;
			if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.south.info, (int)(ratio_x * cub->walls.south.width), wall_ratio * cub->walls.south.height), i, column);
			i++;
		}
	}
	if (wall_type == wall_below)
	{
		while (i < wall_end && i < WIN_HEIGHT)
		{
			wall_ratio = (i - wall_start) / wall_height;
			if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.north.info, (int)(ratio_x * cub->walls.north.width), wall_ratio * cub->walls.north.height), i, column);
			i++;
		}
	}
	if (wall_type == wall_left)
	{
		while (i < wall_end && i < WIN_HEIGHT)
		{
			wall_ratio = (i - wall_start) / wall_height;
			if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.west.info, (int)(ratio_y * cub->walls.west.width), wall_ratio * cub->walls.west.height), i, column);
			i++;
		}
	}
	if (wall_type == wall_right)
	{
		while (i < wall_end && i < WIN_HEIGHT)
		{
			wall_ratio = (i - wall_start) / wall_height;
			if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.east.info, (int)(ratio_y * cub->walls.east.width), wall_ratio * cub->walls.east.height), i, column);
			i++;
		}
	}
}	
