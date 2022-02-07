#include "../headers/cub3d.h"

void	draw_fov(t_ray rays[WIN_WIDTH], t_data *cub, int colour)
{
	t_direction	center;
	int			i;

	center.x = cub->player.position.x;
	center.y = cub->player.position.y;
	i = 0;
	while (i < WIN_WIDTH)
	{
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, center.x + rays[i].direction.x * 50, center.y + rays[i].direction.y * 50, colour);
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
		j = -1;
		while (++j < WIN_WIDTH)
			ft_put_img2(&cub->sheet, cub->floor, i, j);
		i++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
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
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
}

void	ft_draw_all(t_data *cub)
{
	draw_floor(cub);
	draw_ceiling(cub);
	ft_draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
}
