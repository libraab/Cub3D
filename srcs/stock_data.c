#include "../headers/cub3d.h"

void	ft_init_img(t_img *img)
{
	img->img = NULL;
	img->width = 0;
	img->height = 0;
}

t_player	init_player(char **map)
{
	int			i;
	int			j;
	t_player	player;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' \
					|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				player.position.y = i * TILE_SIZE;
				player.position.x = j * TILE_SIZE;
				player.direction = starting_direction(map[i][j]);
			}
			j++;
		}
		i++;
	}
	ft_init_img(&player.img);
	return (player);
}

void	ft_init_data(t_data *cub, char **av)
{
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	cub->sheet.img = mlx_new_image(cub->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	ft_stock_map(cub, av[1]);
	ft_stock_texture(cub, av[1]);
	ft_init_img(&cub->wall);
	ft_init_img(&cub->frame);
	cub->player = init_player(cub->map);
	cast_ray(cub->ray, cub->player);
	start_dda(cub);
	cub->mouse_x = 0;
}

int	get_map_width(char **map)
{
	int	i;
	int	width;

	width = 0;
	i = 0;
	while (map[i])
	{
		if (width <= (int)ft_strlen(map[i]))
			width = (int)ft_strlen(map[i]);
		i++;
	}
	return (width);
}

void	fill_blanks(char **map)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (map[i])
	{
		tmp = malloc(get_map_width(map) * sizeof(char) + 1);
		if (!tmp)
			return ;
		j = 0;
		while (j < (int)ft_strlen(map[i]) + 1)
		{
			tmp[j] = map[i][j];	
			j++;
		}
		while (j < get_map_width(map))
			tmp[j++] = '\0';
		free(map[i]);
		map[i] = tmp;
		i++;
	}
}

void	ft_stock_map(t_data *cub, char *file)
{
	int		i;
	int		fd;
	int		ret;
	char	*line;

	i = 0;
	ret = 1;
	cub->map = ft_calloc(sizeof(char *), ft_get_height(file) + 1);
	fd = open(file, O_RDONLY);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ft_is_direction(line[0])
			|| line[0] == 'F' || line[0] == 'C'
			|| line[0] == '\n' || line[0] == '\0')
		{
			free (line);
			continue ;
		}
		cub->map[i++] = ft_strdup(line);
		free (line);
	}
	cub->map[i] = NULL;
	fill_blanks(cub->map);
	ft_valid_chars(cub);
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
	ft_check_double_texture(cub, -1, 0);
}

t_vector	starting_direction(char player_character)
{
	t_vector	direction;

	direction.x = 0;
	direction.y = 0;
	if (player_character == 'N')
	{
		direction.x = 0;
		direction.y = -1;
	}
	else if (player_character == 'E')
	{
		direction.x = 1;
		direction.y = 0;
	}
	else if (player_character == 'S')
	{
		direction.x = 0;
		direction.y = 1;
	}
	else if (player_character == 'W')
	{
		direction.x = -1;
		direction.y = 0;
	}
	return (direction);
}
