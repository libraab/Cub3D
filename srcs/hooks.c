#include "../headers/cub3d.h"

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

int	rotate_player(int keycode, t_data *cub)
{
	if (keycode == KEY_ARROW_LEFT)
		cub->player.direction = rotate_vector(cub->player.direction, -ROTATION_ANGLE);
	if (keycode == KEY_ARROW_RIGHT)
		cub->player.direction = rotate_vector(cub->player.direction, ROTATION_ANGLE);
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
	print_green_dot(cub, (cub->player.position.y / TILE_SIZE * 10) + cub->player.direction.y * 10, (cub->player.position.x / TILE_SIZE * 10) + cub->player.direction.x * 10);
	cast_ray(cub->ray, cub->player);
	start_dda(cub);
	return (0);
}

int	get_map_height(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_horizontal_wall(t_coordinates position, t_vector direction, char **map)
{
	int	coord_x;
	int	coord_y;

	coord_x = (position.x - position.x % TILE_SIZE) / TILE_SIZE;
	coord_y = (position.y - position.y % TILE_SIZE) / TILE_SIZE;
	if (direction.y <= 0 && coord_y > 0)
	{
		if (map[coord_y - 1][coord_x] == '1')
			return (wall_above);
	}
	else if (direction.y >= 0 && coord_y < get_map_height(map))
	{
		if (map[coord_y + 1][coord_x] == '1')
			return (wall_below);
	}
	return (no_wall);
}

int	check_vertical_wall(t_coordinates position, t_vector direction, char **map)
{
	int	coord_x;
	int	coord_y;

	coord_x = (position.x - position.x % TILE_SIZE) / TILE_SIZE;
	coord_y = (position.y - position.y % TILE_SIZE) / TILE_SIZE;
	if (direction.x <= 0 && coord_x > 0)
	{
		if (map[coord_y][coord_x - 1] == '1')
			return (wall_left);
	}
	else if (direction.x >= 0 && coord_x < (int)ft_strlen(map[coord_y]))
	{
		 if (map[coord_y][coord_x + 1] == '1')
			return (wall_right);
	}
	return (no_wall);
}

void	print_green_dot(t_data *cub, int x, int y)
{
	ft_put_img2(&cub->sheet, GREEN, x, y);
	ft_put_img2(&cub->sheet, GREEN, x + 1, y);
	ft_put_img2(&cub->sheet, GREEN, x, y + 1);
	ft_put_img2(&cub->sheet, GREEN, x + 1, y + 1);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
}

int	player_movement(int keycode, t_data *cub)
{
	if (keycode == rotation_key(keycode) || keycode == movement_key(keycode))
	{
		if (keycode == rotation_key(keycode))
			rotate_player(keycode, cub);
		if (keycode == movement_key(keycode))
			move_player(keycode, cub);
		print_green_dot(cub, (cub->player.position.y / TILE_SIZE * 10) + cub->player.direction.y * 10, (cub->player.position.x / TILE_SIZE * 10) + cub->player.direction.x * 10);
		cast_ray(cub->ray, cub->player);
		start_dda(cub);
	}
	return (0);
}
