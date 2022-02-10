#include "../headers/cub3d.h"

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
	if (x > cub->mouse_x + 10)
	{
		rotate_player(KEY_ARROW_RIGHT, cub);
		cub->mouse_x = x;
	}
	else if (x < cub->mouse_x - 10)
	{
		rotate_player(KEY_ARROW_LEFT, cub);
		cub->mouse_x = x;
	}
	print_green_dot(cub, (cub->player.pos.y * 10) + cub->player.direction.y
		* 10, (cub->player.pos.x * 10) + cub->player.direction.x * 10);
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
		print_green_dot(cub, (cub->player.pos.y * 10) + cub->player.direction.y
			* 10, (cub->player.pos.x * 10) + cub->player.direction.x * 10);
		cast_ray(cub->ray, cub->player);
		start_dda(cub);
	}
	return (0);
}
