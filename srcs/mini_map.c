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
	while (++i < 16)//honrizontal wall
	{
		ft_put_img(&cub->sheet, &cub->player.img, (float)i * 10, 0.0);
		ft_put_img(&cub->sheet, &cub->player.img, (float)i * 10, 150.0);
	}
	j = -1;
	while (++j < 15)//vertical wall
	{
		ft_put_img(&cub->sheet, &cub->player.img, 0.0, (float)j * 10);
		ft_put_img(&cub->sheet, &cub->player.img, 150.0, (float)j * 10);
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

/*void	ft_draw_minimap(t_data *c)
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
				ft_put_img(&c->sheet, &c->mini_wall, (float)x * 10, (float)y * 10);
			else if ((x != (int)floor(c->player.position.x)
					|| (y != (int)floor(c->player.position.y)
						&& is_inside_map(c->map.map[y][x]))))
				ft_put_img(&c->sheet, &c->frame, (float)x * 10, (float)y * 10);
			else if (is_inside_map(c->map.map[y][x]))
				ft_put_img(&c->sheet, &c->player.img, (float)x * 10, (float)y * 10);
		}
	}
}*/

void	ft_draw_minimap(t_data *c)
{
	char **movinmap;
	movinmap = ft_calloc(sizeof(char *), 17);
	int i = 0;
	while (i < 16)
	{
		movinmap[i] = ft_calloc(sizeof(char), 16);
		i++;
	}
	int width = get_map_width(c->map.map);
	int height = get_map_height(c->map.map);
	int	x = (int)c->player.position.x;
	int	y = (int)c->player.position.y;
	int start_y = 0;
	int start_x = 0;
	int end_y = 0;
	int end_x = 0;
	//printf("player [%c] is at[%d][%d]\n", c->map.map[y][x], y, x);
	
	if (y - 7 >= 0)
	{
		start_y = y - 7;
		if (y + 7 <= height)
			end_y = y + 7;
		else if (y + 7 > height)
		{
			end_y = height - 1;
			if (start_y - y + 7 - end_y > 0)
				start_y -= (y + 7 - end_y);
			else
				start_y = 0;
		}
	}
	else if (y - 7 < 0)
	{
		start_y = 0;
		if(y + 7 + ((y -7) * -1) < height)
			end_y = y + 7 + ((y - 7) * -1);
		else
			end_y = height;
	}
	
	if (x - 7 >= 0)
	{
		start_x = x - 7;
		if (x + 7 <= width)
			end_x = x + 7;
		else if (x + 7 > width)
		{
			end_x = width - 1;
			if (start_x - (x + 7 - end_x) > 0)
				start_x -= (x + 7 - end_x);
			else
				start_x = 0;
		}
	}
	else if (x - 7 < 0)
	{
		start_x = 0;
		if(x + 7 + ((x - 7) * -1) < width)
			end_x = x + 7 + ((x - 7) * -1);
		else
			end_x = width;
	}
	// printf("[%d]", start_y);
	// printf("[%d]\n", end_y);
	// printf("[%d]", start_x);
	// printf("[%d]\n", end_x);

	// for (int k = start_y; k < end_y; k++)
	// {
	// 	for (int l = start_x; l < end_x; l++)
	// 		printf("%c", c->map.map[k][l]);
	// 	printf("\n");
	// }
	int j = 0;
	i = 0;
	while (start_y <= end_y && c->map.map[start_y])
	{
		x = start_x;
		j = 0;
		while(x <= end_x && c->map.map[start_y][x])
		{
			movinmap[i][j]= c->map.map[start_y][x];
			movinmap[i][++j]= 0;
			x++;
		}
		i++;
		start_y++;
	}
	// for (int k = 0; movinmap[k]; k++)
	// 	printf("[%s]\n", movinmap[k]);
	
	int count1 =0;
	int count2 =0;
	while(movinmap[count1])
	{
		count2 = 0;
		while(movinmap[count1][count2])
		{
			if (c->map.map[count1][count2] == '1')
				ft_put_img(&c->sheet, &c->mini_wall, (float)count2 * 10, (float)count1 * 10);
			else if (c->map.map[count1][count2] != ' ')
				ft_put_img(&c->sheet, &c->frame, (float)count2 * 10, (float)count1 * 10);
			if (count2 == (int)c->player.position.x && count1 == (int)c->player.position.y)
				ft_put_img(&c->sheet, &c->player.img, (float)count2 * 10, (float)count1 * 10);
			count2++;
		}
		count1++;
	}
}

void	print_green_dot(t_data *cub, int x, int y)
{
	ft_put_img2(&cub->sheet, GREEN, x, y);
	ft_put_img2(&cub->sheet, GREEN, x + 1, y);
	ft_put_img2(&cub->sheet, GREEN, x, y + 1);
	ft_put_img2(&cub->sheet, GREEN, x + 1, y + 1);
}
