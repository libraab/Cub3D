#include "../headers/cub3d.h"

void	ft_valid_chars(t_data *cub)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] != ' ' && cub->map[i][j] != '0'
				&& cub->map[i][j] != '1' && !ft_is_direction(cub->map[i][j]))
				ft_error(3);
			if (ft_is_direction(cub->map[i][j]))
				count++;
		}
	}
	if (count == 0)
		ft_error(4);
	if (count != 1)
		ft_error(5);
}

void	ft_valid_walls(t_data *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == '0' && i == 0 && j == 0)
				ft_error(6);
			if (cub->map[i][j] == '0' || ft_is_direction(cub->map[i][j]))
			{
				if (!ft_north_wall(cub->map, i, j)
					|| !ft_south_wall(cub->map, i, j)
					|| !ft_east_wall(cub->map, i, j)
					|| !ft_west_wall(cub->map, i, j))
					ft_error(6);
			}
		}
	}
}

void	ft_check_double_texture(t_data *cub, int i, int e)
{
	int	n;
	int	s;
	int	w;

	n = 0;
	s = 0;
	w = 0;
	while (cub->tex[++i])
	{
		if (cub->tex[i][0] == 'N' && cub->tex[i][1] == 'O')
			n++;
		else if (cub->tex[i][0] == 'S' && cub->tex[i][1] == 'O')
			s++;
		else if (cub->tex[i][0] == 'E' && cub->tex[i][1] == 'A')
			e++;
		else if (cub->tex[i][0] == 'W' && cub->tex[i][1] == 'E')
			w++;
	}
	if (i != 6 || n != 1 || s != 1 || w != 1 || e != 1)
		ft_error(8);
	ft_valid_texture(cub);
}

int	get_surface(char *surface)
{
	char	**tab;
	int		colour;

	tab = ft_split(surface, ',');
	colour = create_rgb(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]));
	ft_free_double(tab);
	return (colour);
}

void	ft_check_digits(char *str)
{
	char	**tab;
	int		i;

	i = ft_skip_spaces(str, 1, 0);
	tab = ft_split(&str[i], ',');
	i = -1;
	while (tab[++i])
	{
		if (ft_atoi(tab[i]) < 0 || ft_atoi(tab[i]) > 255)
			ft_error(8);
	}
	if (i > 3)
		ft_error(8);
	ft_free_double(tab);
}
