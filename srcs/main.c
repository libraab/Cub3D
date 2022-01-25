/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:18:11 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/25 04:38:55 by bleotard         ###   ########.fr       */
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

int	ft_exit(void)
{
	write(1, "Bye Bye!\n", 9);
	exit(0);
}

int	key_release(int keycode)
{
	if (keycode == KEY_ECHAP)
		ft_exit();
	return (0);
}

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

void	draw_fov(t_vector *rays, t_data *cub)
{
	t_vector	center;
	int			i;

	center.x = 800;
	center.y = 450;
	i = 0;
	while (i < WIN_WIDTH)
	{
		mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, center.x + rays[i].x * 200, center.y + rays[i].y * 200, GREEN);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	cub;
	//t_img	mini;
	t_vector	*rays;

	ft_init_data(&cub);
	if (ac < 2 || ac > 2)
		ft_error(0);
	cub.map = ft_calloc(sizeof(char *), ft_get_height(av[1]) + 1);
	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	cub.mini.img = mlx_new_image(cub.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	cub.player = init_player(cub.map);
	printf("start x: %f, start y: %f, dir x: %f, dir y: %f\n", cub.player.position.x, cub.player.position.y, cub.player.direction.x, cub.player.direction.y);
	rays = cast_rays(cub.player.direction);
	draw_fov(rays, &cub);
	ft_draw_frame(&cub);
	//ft_draw_minimap(&cub);
	mlx_hook(cub.win_ptr, ON_DESTROY, 0, ft_exit, NULL);
	mlx_hook(cub.win_ptr, ON_KEYUP, 0, key_release, &cub);
	mlx_loop(cub.mlx_ptr);
	free(rays);
	ft_free_double(cub.tex);
	ft_free_double(cub.map);
	return (0);
}
