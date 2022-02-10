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
			cub->minimap[i][j] = cub->map.map[tab[0]][x];
			cub->minimap[i][++j] = 0;
			x++;
		}
		i++;
		tab[0]++;
	}
}

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
				ft_put_img(&cub->sheet, &cub->mini_wall, 10 + ((float)j * 10), 10 + ((float)i * 10));
			else if (cub->minimap[i][j] != ' ')
				ft_put_img(&cub->sheet, &cub->frame, 10 + ((float)j * 10), 10 + ((float)i * 10));
			if (j == (int)cub->player.position.x && i == (int)cub->player.position.y)
			{
				ft_put_img(&cub->sheet, &cub->player.img, 10 + ((float)j * 10), 10 + ((float)i * 10));
			}
			j++;
		}
		i++;
	}
}
int		*ft_stock_tab(t_data *cub, int *tab)
{
	tab[0] = (int)cub->player.position.y - 7;
	tab[1] = (int)cub->player.position.y + 7;
	tab[2] = (int)cub->player.position.x - 7;
	tab[3] = (int)cub->player.position.x + 7;
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
	if (tab[3] > cub->map_width)
	{
		tab[2] -= (tab[3] - cub->map_width);
		tab[3] = cub->map_width;
	}
	return (tab);
}

void	ft_draw_minimap(t_data *cub)
{
	int	*tab = ft_calloc(sizeof(int), 4);
	tab = ft_stock_tab(cub, tab);
	ft_stock_minimap(cub, tab);
	ft_print_minimap(cub);
}

void	print_green_dot(t_data *cub, int x, int y)
{
	ft_put_img2(&cub->sheet, GREEN, x, y);
	ft_put_img2(&cub->sheet, GREEN, x + 1, y);
	ft_put_img2(&cub->sheet, GREEN, x, y + 1);
	ft_put_img2(&cub->sheet, GREEN, x + 1, y + 1);
}
