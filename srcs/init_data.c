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
				player.pos.y = i;
				player.pos.x = j;
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
	cub->sheet.info.addr = mlx_get_data_addr(cub->sheet.img,
			&cub->sheet.info.bits_per_pixel, &cub->sheet.info.line_len,
			&cub->sheet.info.endian);
	ft_stock_map(cub, av[1]);
	ft_stock_texture(cub, av[1], 0, 1);
	ft_init_img(&cub->mini_wall);
	ft_init_img(&cub->frame);
	cub->minimap = NULL;
	cub->player = init_player(cub->map.map);
	cast_ray(cub->ray, cub->player);
	start_dda(cub);
	cub->mouse_x = 0;
	cub->map_width = get_map_width(cub->map.map);
	cub->map_height = get_map_height(cub->map.map);
}
