#include "../headers/cub3d.h"

void	ft_print_texture(t_data *cub, int wall_height, int wall_type, int column)
{
	//int	texture_column;
	//t_img	texture;
	int		i;
	float	ratio_x;
	float	ratio_y;
	float	wall_ratio;
	float	wall_start;
	float	wall_end;

	cub->map.x = (int)cub->ray[column].impact.x;
	cub->map.y = (int)cub->ray[column].impact.y;
	ratio_x = cub->ray[column].impact.x - cub->map.x;
	ratio_y = cub->ray[column].impact.y - cub->map.y;
	//printf("ratio_x: %f, texture width: %d, printed column: %f\n", ratio_x, cub->walls.north.width, ratio_x * cub->walls.north.width);
	wall_end = WIN_HEIGHT / 2 + wall_height / 2;
	wall_start = WIN_HEIGHT / 2 - wall_height / 2;
	i = wall_start;
	if (wall_type == wall_above)
	{
		while (i < wall_end && i < WIN_HEIGHT)
		{
			wall_ratio = (i - wall_start) / wall_height;
			if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.south.info, (int)(ratio_x * cub->walls.south.width), wall_ratio * cub->walls.south.height), i, column);
			i++;
		}
	}
	if (wall_type == wall_below)
	{
		while (i < wall_end && i < WIN_HEIGHT)
		{
			wall_ratio = (i - wall_start) / wall_height;
			if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.north.info, (int)(ratio_x * cub->walls.north.width), wall_ratio * cub->walls.north.height), i, column);
			i++;
		}
	}
	if (wall_type == wall_left)
	{
		while (i < wall_end && i < WIN_HEIGHT)
		{
			wall_ratio = (i - wall_start) / wall_height;
			if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.west.info, (int)(ratio_y * cub->walls.west.width), wall_ratio * cub->walls.west.height), i, column);
			i++;
		}
	}
	if (wall_type == wall_right)
	{
		while (i < wall_end && i < WIN_HEIGHT)
		{
			wall_ratio = (i - wall_start) / wall_height;
			if (i > 0)
				ft_put_img2(&cub->sheet, ft_pixel_get(&cub->walls.east.info, (int)(ratio_y * cub->walls.east.width), wall_ratio * cub->walls.east.height), i, column);
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
