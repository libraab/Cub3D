#include "../headers/cub3d.h"

int	main(int ac, char **av)
{
	t_data	cub;

	if (ac != 2)
		ft_error(0);
	ft_init_data(&cub, av);
	mlx_hook(cub.win_ptr, ON_DESTROY, 0, ft_exit, NULL);
	mlx_hook(cub.win_ptr, ON_KEYUP, 0, key_release, &cub);
	mlx_hook(cub.win_ptr, ON_KEYDOWN, 0, player_movement, &cub);
	mlx_loop(cub.mlx_ptr);
	ft_free_double(cub.tex);
	ft_free_double(cub.map.map);
	ft_free_double(cub.minimap);
	return (0);
}
