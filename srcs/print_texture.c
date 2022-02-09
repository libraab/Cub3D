#include "../headers/cub3d.h"

void	ft_print_texture(t_data *cub, int wall_height, int wall_type, int column)
{
	//int	texture_column;
	//t_img	texture;
	int		i;

	(void)wall_height;
	cub->map.x = (int)cub->ray[column].impact.x;
	cub->map.y = (int)cub->ray[column].impact.y;
	if (wall_type == wall_above)
	{
		i = 0;
		while (i < cub->walls.south.height)
		{
			if (i < WIN_HEIGHT)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.south.info, cub->map.x, i), i, column);
			i++;
		}
	}
	if (wall_type == wall_below)
	{
		i = 0;
		while (i < cub->walls.north.height)
		{
			if (i < WIN_HEIGHT)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.north.info, cub->map.x, i), i, column);
			i++;
		}
	}
	if (wall_type == wall_left)
	{
		i = 0;
		while (i < cub->walls.east.height)
		{
			if (i < WIN_HEIGHT)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.east.info, cub->map.x, i), i, column);
			i++;
		}
	}
	if (wall_type == wall_right)
	{
		i = 0;
		while (i < cub->walls.west.height)
		{
			if (i < WIN_HEIGHT)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.west.info, cub->map.x, i), i, column);
			i++;
		}
	}
}	










// int	i = 50;
// int	j = 0;
// int	k = 0;
// int	l = 400; //start of the wall (x)
// int	m = 200;
// if (x == 1) //back
// {
// 	i -= 10;
// 	m += 10;
// 	j = WIN_HEIGHT - WIN_HEIGHT / 2 + 10;
// }
// else if (x == 0) //start state
// {
// 	int	i = 50;
// 	int	j = WIN_HEIGHT - WIN_HEIGHT / 2;
// 	int	k = 0;
// 	int	l = 400; //start of the wall (x)
// 	int	m = 200;
// 	while (++i < j)
// 	{
// 		k = 0;
// 		ft_put_img2(&cub->sheet, RED, i, 400);
// 		while (++k < m)
// 			ft_put_img2(&cub->sheet, RED, i, l + k);
// 	}
// 	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
// 	return ;
// }
// else if (x == -1) //forward
// {
// 	i += 10;
// 	l -= 10;
// 	m -= 10;
// 	j = WIN_HEIGHT - WIN_HEIGHT / 2;
// }
// // if (x > 1)
// // {
// // 	i = 200;
// // 	j = WIN_HEIGHT - WIN_HEIGHT/3;
// // }
// ft_draw_all(cub);
// while (++i < j)
// {
// 	k = 0;
// 	ft_put_img2(&cub->sheet, RED, i, 400);
// 	while (++k < m)
// 		ft_put_img2(&cub->sheet, RED, i, l + k);
// }
//	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
