#include "../headers/cub3d.h"

void	ft_stock_map(t_data *cub, char *file)
{
	int		i;
	int		fd;
	int		ret;
	char	*line;

	i = 0;
	ret = 1;
	cub->map.map = ft_calloc(sizeof(char *), ft_get_height(file) + 1);
	fd = open(file, O_RDONLY);
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
	cub->map.map[i] = NULL;
	fill_blanks(cub->map.map);
	ft_valid_chars(cub);
	close (fd);
}

void	get_wall_textures(t_data *cub, char *texture_name, t_walls *walls)
{
	if (texture_name[0] == 'N')
	{
		texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
		walls->north.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, &walls->north.width, &walls->north.height);
		walls->north.info.addr = mlx_get_data_addr(walls->north.img, &walls->north.info.bits_per_pixel,
				&walls->north.info.line_len, &walls->north.info.endian);
	}
	else if (texture_name[0] == 'S')
	{
		texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
		walls->south.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, &walls->south.width, &walls->south.height);
		walls->south.info.addr = mlx_get_data_addr(walls->south.img, &walls->south.info.bits_per_pixel,
				&walls->south.info.line_len, &walls->south.info.endian);
	}
	else if (texture_name[0] == 'E')
	{
		texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
		walls->east.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, &walls->east.width, &walls->east.height);
		walls->east.info.addr = mlx_get_data_addr(walls->east.img, &walls->east.info.bits_per_pixel,
				&walls->east.info.line_len, &walls->east.info.endian);
	}
	else if (texture_name[0] == 'W')
	{
		texture_name = ft_strtrim(ft_strdup(texture_name), "./SONWEA ");
		walls->west.img = mlx_xpm_file_to_image(cub->mlx_ptr, texture_name, &walls->west.width, &walls->west.height);
		walls->west.info.addr = mlx_get_data_addr(walls->west.img, &walls->west.info.bits_per_pixel,
				&walls->west.info.line_len, &walls->west.info.endian);
	}
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
		{
			cub->tex[i++] = ft_strtrim(ft_strdup(line), " ");
			get_wall_textures(cub, line, &cub->walls);
		}
		free (line);
	}
	cub->tex[i] = NULL;
	close (fd);
	ft_check_double_texture(cub, -1, 0);
}
