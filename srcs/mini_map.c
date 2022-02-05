#include "../headers/cub3d.h"

void	ft_update_map(t_data *cub, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (ft_is_direction(cub->map[i][j]))
			{
				cub->map[i + x][j + y] = cub->map[i][j];
				cub->map[i][j] = '0';
				j++;
			}
		}
	}
}

void	ft_draw_frame(t_data *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 20)
	{
		ft_put_img(&cub->sheet, &cub->frame, (float)i * 10, 0.0);
		ft_put_img(&cub->sheet, &cub->frame, (float)i * 10, 150.0);
	}
	j = -1;
	while (++j < 15)
	{
		ft_put_img(&cub->sheet, &cub->frame, 0.0, (float)j * 10);
		ft_put_img(&cub->sheet, &cub->frame, 190.0, (float)j * 10);
	}
}

int	is_inside_map(char c)
{
	if (!c)
		return (0);
	else if (c == '0' || ft_is_direction(c))
		return (1);
	return (0);
}

void	ft_draw_minimap(t_data *cub)
{
	int	x;
	int	y;

	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == '1')
				ft_put_img(&cub->sheet, &cub->wall, (float)x * 10, (float)y * 10);
			else if ((x != (int)floor(cub->player.position.x) || (y != (int)floor(cub->player.position.y) && is_inside_map(cub->map[y][x]))))
				ft_put_img(&cub->sheet, &cub->frame, (float)x * 10, (float)y * 10);
			else if (is_inside_map(cub->map[y][x]))
				ft_put_img(&cub->sheet, &cub->player.img, (float)x * 10, (float)y * 10);
		}
	}
}
