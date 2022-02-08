#include "../headers/cub3d.h"

void	ft_update_map(t_data *cub, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map.map[++i])
	{
		j = -1;
		while (cub->map.map[i][++j])
		{
			if (ft_is_direction(cub->map.map[i][j]))
			{
				cub->map.map[i + x][j + y] = cub->map.map[i][j];
				cub->map.map[i][j] = '0';
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
	while (++i < 15)
	{
		ft_put_img(&cub->sheet, &cub->frame, (float)i * 10, 0.0);
		ft_put_img(&cub->sheet, &cub->frame, (float)i * 10, 140.0);
	}
	j = -1;
	while (++j < 15)
	{
		ft_put_img(&cub->sheet, &cub->frame, 0.0, (float)j * 10);
		ft_put_img(&cub->sheet, &cub->frame, 140.0, (float)j * 10);
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

void	ft_draw_minimap(t_data *c)
{
	int	x;
	int	y;

	y = -1;
	while (c->map.map[++y])
	{
		x = -1;
		while (c->map.map[y][++x])
		{
			if (c->map.map[y][x] == '1')
				ft_put_img(&c->sheet, &c->wall, (float)x * 10, (float)y * 10);
			else if ((x != (int)floor(c->player.position.x)
					|| (y != (int)floor(c->player.position.y)
						&& is_inside_map(c->map.map[y][x]))))
				ft_put_img(&c->sheet, &c->frame, (float)x * 10, (float)y * 10);
			else if (is_inside_map(c->map.map[y][x]))
				ft_put_img(&c->sheet, &c->player.img, (float)x * 10, (float)y * 10);
		}
	}
}

/*void	ft_draw_minimap(t_data *c)
{
	int	x;
	int	y;
	int start_x = 0;
	int start_y = 0;
	int end_x = 0;
	int end_y = 0;

	y = -1;
	while (c->map.map[++y])
	{
		x = 0;
		while (c->map.map[y][x] && !ft_is_direction(c->map.map[y][x]))
			x++;
	}
	if (x - 7 >= 0)
		start_x = x - 7;
	if (x + 7 <= get_map_width(c->map.map))
		end_x = x + 7;
	if (y - 7 >= 0)
		start_y = y - 7;
	if (y + 7 <= get_map_height(c->map.map))
		end_y = y + 7;
	printf("x start at [%d] and end at [%d]\n", start_x, end_x);
	printf("y start at [%d] and end at [%d]\n", start_y, end_y);
	while (start_y < end_y)
	{
		start_x = x - 7;
		while(start_x < end_x)
		{
			if (c->map.map[start_y][start_x] == '1')
				ft_put_img(&c->sheet, &c->wall, (float)start_x * 10, (float)start_y * 10);
			else if (c->map.map[start_y][start_x] != ' ')
				ft_put_img(&c->sheet, &c->frame, (float)start_x * 10, (float)start_y * 10);
			if (start_x == (int)c->player.position.x) && (start_y == (int)c->player.position.y))
				ft_put_img(&c->sheet, &c->player.img, (float)x * 10, (float)y * 10);
		}
		start_y++;
	}
}*/

void	print_green_dot(t_data *cub, int x, int y)
{
	ft_put_img2(&cub->sheet, GREEN, x, y);
	ft_put_img2(&cub->sheet, GREEN, x + 1, y);
	ft_put_img2(&cub->sheet, GREEN, x, y + 1);
	ft_put_img2(&cub->sheet, GREEN, x + 1, y + 1);
}
