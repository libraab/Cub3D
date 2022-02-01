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

int	main(int ac, char **av)
{
	t_data	cub;

	if (ac != 2)
		ft_error(0);
	ft_init_data(&cub, av);
	ft_valid_walls(&cub);
	ft_define_img(&cub);
	ft_print_all(&cub);
	mlx_hook(cub.win_ptr, ON_DESTROY, 0, ft_exit, NULL);
	mlx_hook(cub.win_ptr, ON_KEYUP, 0, key_release, &cub);
	mlx_hook(cub.win_ptr, ON_KEYDOWN, 0, player_movement, &cub);
	mlx_hook(cub.win_ptr, ON_MOUSEMOVE, 0, mouse_move, &cub);
	ft_print_texture(&cub);
	mlx_loop(cub.mlx_ptr);
	ft_free_double(cub.tex);
	ft_free_double(cub.map);
	return (0);
}
