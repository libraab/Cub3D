#include "../headers/cub3d.h"

void	draw_floor(t_data *cub)
{
	int	i;
	int	j;

	i = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			ft_put_img2(&cub->sheet, cub->floor, i, j);
		i++;
	}
}

void	draw_ceiling(t_data *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT / 2)
	{
		j = 0;
		while (++j < WIN_WIDTH)
			ft_put_img2(&cub->sheet, cub->ceiling, i, j);
		i++;
	}
}
