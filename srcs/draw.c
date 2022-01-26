#include "../headers/cub3d.h"

void ft_draw_frame(t_data *cub)
{
	int	i;
	int	j;

	i = 49;
	while(++i < 250)
	{
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, i, 50, RED);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, i, 51, RED);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, i, 199, RED);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, i, 200, RED);
		if (i < 201)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 50, i, RED);
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 51, i, RED);
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 250, i, RED);
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 251, i, RED);
		}
		j = 51;
		while(++j < 199)
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, i, j, GOLD);
	}
}

void	draw_fov(t_ray rays[WIN_WIDTH], t_data *cub)
{
	t_vector	center;
	int			i;

	center.x = WIN_WIDTH / 2;
	center.y = WIN_HEIGHT / 2;
	i = 0;
	while (i < WIN_WIDTH)
	{
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, center.x + rays[i].direction.x * 200, center.y + rays[i].direction.y * 200, create_rgb(255, 0, 0));
		i++;
	}
}

void	draw_floor(t_data *cub)
{
	int	i;
	int	j;

	i = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, j, i, cub->floor);
			j++;
		}
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
		while (j < WIN_WIDTH)
		{
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, j, i, cub->ceiling);
			j++;
		}
		i++;
	}
}
