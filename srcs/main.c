/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:18:11 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/20 13:15:41 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	ft_get_height(char *file)
{
	int		fd;
	int		i;
	char	*line;

	i = ft_strlen(file) - 1;
	if (file[i] != 'b' && file[i - 1] != 'u'
		&& file[i - 2] != 'c'
		&& file[i - 3] != '.')
		ft_error(1);
	fd = open(file, O_DIRECTORY);
	if (fd != -1)
		ft_error(2);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(7);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		i++;
		free(line);
	}
	i++;
	free(line);
	close (fd);
	return (i);
}

int	ft_exit(int keycode, t_data *win)
{
	(void)keycode;
	(void)win;
	write(1, "Bye Bye!\n", 9);
	exit(0);
	return (0);
}

void ft_draw_frame(t_data *cub)
{
	int	i;
	int	j;

	i = -1;
	while(++i < 200)
	{
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 50 + i, 50, 0xff0000);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 50 + i, 51, 0xff0000);
		j = -1;
		while(++j < 150)
			mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 52 + i, 50 + j, 0xffd700);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 50 + i, 200, 0xff0000);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 50 + i, 199, 0xff0000);
	}
	i = -1;
	while(++i < 150)
	{
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 50, 50 + i, 0xff0000);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 51, 50 + i, 0xff0000);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 250, 50 + i, 0xff0000);
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, 251, 50 + i, 0xff0000);
	}
}

int	main(int ac, char **av)
{
	t_data	cub;
	//t_img	mini;

	ft_init_data(&cub);
	if (ac < 2 || ac > 2)
		ft_error(0);
	cub.map = ft_calloc(sizeof(char *), ft_get_height(av[1]) + 1);
	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, 1500, 1000, "cub3D");
	ft_draw_frame(&cub);
	mlx_hook(cub.win_ptr, 17, 0, ft_exit, &cub);
	/*
	mlx_hook(win->win_ptr, 2, 1L << 0, ft_deal_key, win);
	mlx_hook(win->win_ptr, 3, 1L << 1, ft_release_key, win);
	*/
	mlx_loop(cub.mlx_ptr);
	ft_free_double(cub.tex);
	ft_free_double(cub.map);
	return (0);
}
