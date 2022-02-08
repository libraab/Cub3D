#include "../headers/cub3d.h"

int	ft_exit(void)
{
	write(1, "Bye Bye!\n", 9);
	exit(0);
}

int	ft_is_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_map_height(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
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
