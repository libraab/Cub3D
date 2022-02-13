#include "../../headers/cub3d.h"

void	get_vi_images(t_data *cub)
{
	cub->vi1.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/vi/vi1.xpm",
			&cub->vi1.width, &cub->vi1.height);
	cub->vi1.info.addr = mlx_get_data_addr(cub->vi1.img,
			&cub->vi1.info.bits_per_pixel, &cub->vi1.info.line_len,
			&cub->vi1.info.endian);
	cub->vi2.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/vi/vi2.xpm",
			&cub->vi2.width, &cub->vi2.height);
	cub->vi2.info.addr = mlx_get_data_addr(cub->vi2.img,
			&cub->vi2.info.bits_per_pixel, &cub->vi2.info.line_len,
			&cub->vi2.info.endian);
	cub->vi3.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/vi/vi3.xpm",
			&cub->vi3.width, &cub->vi3.height);
	cub->vi3.info.addr = mlx_get_data_addr(cub->vi3.img,
			&cub->vi3.info.bits_per_pixel, &cub->vi3.info.line_len,
			&cub->vi3.info.endian);
	cub->vi4.img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/vi/vi4.xpm",
			&cub->vi4.width, &cub->vi4.height);
	cub->vi4.info.addr = mlx_get_data_addr(cub->vi4.img,
			&cub->vi4.info.bits_per_pixel, &cub->vi4.info.line_len,
			&cub->vi4.info.endian);
}

void	print_vi(int i, t_data *cub)
{
	start_dda(cub);
	if (i == 0)
		ft_put_img(&cub->sheet, &cub->vi2, 500, 400);
	if (i == 1)
		ft_put_img(&cub->sheet, &cub->vi1, 500, 400);
	if (i == 2)
		ft_put_img(&cub->sheet, &cub->vi3, 500, 400);
	if (i == 3)
		ft_put_img(&cub->sheet, &cub->vi4, 500, 400);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
}

int	ft_animation(t_data *cub)
{
	static int	i = 0;

	if ((int)cub->player.pos.x == 4 && (int)cub->player.pos.y == 5)
	{
		usleep(150000);
		print_vi(i, cub);
		i++;
		if (i == 4)
			i = 0;
	}
	return (0);
}
