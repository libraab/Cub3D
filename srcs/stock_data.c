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
		init_tex_ns(cub, texture_name, walls, 0);
	else if (texture_name[0] == 'S')
		init_tex_ns(cub, texture_name, walls, 1);
	else if (texture_name[0] == 'E')
		init_tex_ew(cub, texture_name, walls, 0);
	else if (texture_name[0] == 'W')
		init_tex_ew(cub, texture_name, walls, 1);
}

void	ft_stock_texture(t_data *cub, char *file, int i, int ret)
{
	int		fd;
	char	*line;

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
