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
		i = WIN_HEIGHT / 2 - wall_height / 2;
			while (i < WIN_HEIGHT / 2 + wall_height / 2 && i < WIN_HEIGHT)
			{
				if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.south.info, 10, 10), i, column);
			i++;
			}
	}
	if (wall_type == wall_below)
	{
		i = WIN_HEIGHT / 2 - wall_height / 2;
			while (i < WIN_HEIGHT / 2 + wall_height / 2 && i < WIN_HEIGHT)
			{
				if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.north.info, 10, 10), i, column);
			i++;
			}
	}
	if (wall_type == wall_left)
	{
		i = WIN_HEIGHT / 2 - wall_height / 2;
			while (i < WIN_HEIGHT / 2 + wall_height / 2 && i < WIN_HEIGHT)
			{
				if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.east.info, 10, 10), i, column);
			i++;
			}
	}
	if (wall_type == wall_right)
	{
		i = WIN_HEIGHT / 2 - wall_height / 2;
			while (i < WIN_HEIGHT / 2 + wall_height / 2 && i < WIN_HEIGHT)
			{
				if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.west.info, 10, 10), i, column);
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
