/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:18:11 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/26 18:57:27 by bleotard         ###   ########.fr       */
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

int	rotate_player(int keycode, t_data *cub)
{
	if (keycode == KEY_ARROW_LEFT)
	{
		cub->player.direction = rotate_vector(cub->player.direction, -ROTATION_ANGLE);
		cast_rays(cub->rays, cub->player.direction);
		draw_fov(cub->rays, cub, GOLD);
	}
	if (keycode == KEY_ARROW_RIGHT)
	{
		cub->player.direction = rotate_vector(cub->player.direction, ROTATION_ANGLE);
		cast_rays(cub->rays, cub->player.direction);
		draw_fov(cub->rays, cub, BLUE);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	cub;
	//t_img	sheet;

	if (ac != 2)
		ft_error(0);
	ft_init_data(&cub, av);
	ft_parse(&cub);
	ft_define_img(&cub);
	draw_floor(&cub);
	draw_ceiling(&cub);	
	ft_draw_minimap(&cub);
	draw_fov(cub.rays, &cub, RED);
	mlx_hook(cub.win_ptr, ON_DESTROY, 0, ft_exit, NULL);
	mlx_hook(cub.win_ptr, ON_KEYUP, 0, key_release, &cub);
	mlx_hook(cub.win_ptr, ON_KEYDOWN, 0, rotate_player, &cub);
	mlx_loop(cub.mlx_ptr);
	ft_free_double(cub.tex);
	ft_free_double(cub.map);
	return (0);
}
