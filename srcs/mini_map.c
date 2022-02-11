#include "../headers/cub3d.h"

void	ft_draw_frame(t_data *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 16)
	{
		ft_put_img(&cub->sheet, &cub->player.img, (float)i * 10, 0.0);
		ft_put_img(&cub->sheet, &cub->player.img, (float)i * 10, 150.0);
	}
	j = -1;
	while (++j < 15)
	{
		ft_put_img(&cub->sheet, &cub->player.img, 0.0, (float)j * 10);
		ft_put_img(&cub->sheet, &cub->player.img, 150.0, (float)j * 10);
	}
}

void	ft_stock_minimap(t_data *cub, int *tab)
{
	int	i;
	int	j;
	int	x;

	i = -1;
	j = 0;
	x = 0;
	if (cub->minimap != NULL)
		ft_free_double(cub->minimap);
	cub->minimap = ft_calloc(sizeof(char *), 17);
	while (++i < 16)
		cub->minimap[i] = ft_calloc(sizeof(char), 16);
	i = 0;
	while (tab[0] <= tab[1] && cub->map.map[tab[0]])
	{
		x = tab[2];
		j = 0;
		while (x <= tab[3] && cub->map.map[tab[0]][x])
		{
			if (tab[0] == (int)cub->player.pos.y && x == (int)cub->player.pos.x)
			{
				cub->minimap[i][j] = 'P';
				x++;
			}
			else
				cub->minimap[i][j] = cub->map.map[tab[0]][x++];
			cub->minimap[i][++j] = 0;
		}
		i++;
		tab[0]++;
	}
}
/*
-------------------------------------normed fct
void	ft_stock_minimap(t_data *cub, int *tab, int i, int j)
{
	int	x;

	x = 0;
	if (cub->minimap != NULL)
		ft_free_double(cub->minimap);
	cub->minimap = ft_calloc(sizeof(char *), 17);
	while (++i < 16)
		cub->minimap[i] = ft_calloc(sizeof(char), 16);
	i = 0;
	while (tab[0] <= tab[1] && cub->map.map[tab[0]])
	{
		x = tab[2];
		j = 0;
		while (x <= tab[3] && cub->map.map[tab[0]][x])
		{
			if (tab[0] == (int)cub->player.pos.y && x == (int)cub->player.pos.x)
			{
				cub->minimap[i][j] = 'P';
				x++;
			}
			else
				cub->minimap[i][j++] = cub->map.map[tab[0]][x++];
			cub->minimap[i][++j] = 0;
		}
		i++;
		tab[0]++;
	}
}*/

void	ft_print_minimap(t_data *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub->minimap[i])
	{
		j = 0;
		while (cub->minimap[i][j])
		{
			if (cub->minimap[i][j] == '1')
				ft_put_img(&cub->sheet, &cub->mini_wall, 10 + ((float)j * 10),
					10 + ((float)i * 10));
			else if (cub->minimap[i][j] != ' ')
				ft_put_img(&cub->sheet, &cub->frame, 10 + ((float)j * 10),
					10 + ((float)i * 10));
			if (cub->minimap[i][j] == 'P')
			{
				ft_put_img(&cub->sheet, &cub->player.img, 10 + ((float)j * 10),
					10 +((float)i * 10));
			}
			j++;
		}
		i++;
	}
}

int	*ft_stock_tab(t_data *cub, int *tab)
{
	tab[0] = (int)cub->player.pos.y - 7;
	tab[1] = (int)cub->player.pos.y + 7;
	tab[2] = (int)cub->player.pos.x - 7;
	tab[3] = (int)cub->player.pos.x + 7;
	if (tab[0] < 0)
	{
		tab[1] += (tab[0] * -1);
		tab[0] = 0;
	}
	if (tab[1] > cub->map_height)
	{
		tab[0] -= (tab[1] - cub->map_height);
		tab[1] = cub->map_height;
	}
	if (tab[2] < 0)
	{
		tab[3] += (tab[2] * -1);
		tab[2] = 0;
	}
	else if (tab[3] > cub->map_width)
	{
		tab[2] -= (tab[3] - cub->map_width);
		tab[3] = cub->map_width;
	}
	return (tab);
}

void	ft_draw_minimap(t_data *cub)
{
	int	*tab;

	tab = ft_calloc(sizeof(int), 4);
	tab = ft_stock_tab(cub, tab);
	// if (cub->map_height < 15 && cub->map_width >= 15)
	// {
	// 	tab[0] = 0;
	// 	tab[1] = get_map_height(cub->map.map);
	// }
	// if (cub->map_height >= 15 && cub->map_width < 15)
	// {
	// 	tab[2] = 0;
	// 	tab[3] = get_map_width(cub->map.map);
	// }
	// if (cub->map_height < 15 && cub->map_width < 15)
	// {
	// 	tab[0] = 0;
	// 	tab[1] = get_map_height(cub->map.map);
	// 	tab[2] = 0;
	// 	tab[3] = get_map_width(cub->map.map);
	// }
	// ft_stock_minimap(cub, tab, -1, 0);
	ft_stock_minimap(cub, tab);
	ft_print_minimap(cub);
}
