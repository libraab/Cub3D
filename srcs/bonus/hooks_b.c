#include "../../headers/cub3d.h"

int	key_release(int keycode)
{
	if (keycode == KEY_ECHAP)
		ft_exit();
	return (0);
}

int	rotation_key(int keycode)
{
	if (keycode == KEY_ARROW_LEFT || keycode == KEY_ARROW_RIGHT)
		return (keycode);
	else
		return (0);
}

int	movement_key(int keycode)
{
	if (keycode == KEY_W || keycode == KEY_A \
			|| keycode == KEY_S || keycode == KEY_D)
		return (keycode);
	else
		return (0);
}

int	mouse_move(int x, int y, t_data *cub)
{
	(void)y;
	if (cub->mouse_x == 0)
		cub->mouse_x = x;
	if (x > cub->mouse_x + 10 || x == 1819)
	{
		rotate_player(KEY_ARROW_RIGHT, cub);
		cub->mouse_x = x;
	}
	else if (x < cub->mouse_x - 10 || x == -100)
	{
		rotate_player(KEY_ARROW_LEFT, cub);
		cub->mouse_x = x;
	}
	cast_ray(cub->ray, cub->player);
	start_dda(cub);
	return (0);
}

int	player_movement(int keycode, t_data *cub)
{
	if (keycode == rotation_key(keycode) || keycode == movement_key(keycode))
	{
		if (keycode == rotation_key(keycode))
			rotate_player(keycode, cub);
		if (keycode == movement_key(keycode))
			move_player(keycode, cub);
		cast_ray(cub->ray, cub->player);
		start_dda(cub);
	}
	return (0);
}
