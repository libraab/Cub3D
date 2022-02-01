#include "../headers/cub3d.h"

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

int	ft_tablen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_tabwidth(char **str)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	width = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (j > width)
				width = j;
			j++;
		}
		i++;
	}
	return (width);
}
