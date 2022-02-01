#include "../headers/cub3d.h"

void	ft_print_texture(t_data *cub)
{
	int i = 0;
	while (++i < WIN_HEIGHT)
		ft_put_img2(&cub->sheet, RED, i, 400);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
}
