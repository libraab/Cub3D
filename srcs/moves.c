#include "../headers/cub3d.h"

void	calc_deltas(t_vector direction, int *delta_x, int *delta_y, int distance)
{
	int		step_x;
	int		step_y;

	step_x = calc_step_x(direction, 1);
	step_y = calc_step_y(direction, 1);
	*delta_x = distance / step_x;
	*delta_y = distance / step_y;
}

void	move(t_vector movement_direction, t_player *player, char **map)
{
	int		delta_x;
	int		delta_y;

	calc_deltas(movement_direction, &delta_x, &delta_y, PLAYER_STEP);
	if (check_vertical_wall(player->position, movement_direction, map) == no_wall)
	{
		if (movement_direction.x > 0)
			player->position.x += delta_x;
		else
			player->position.x -= delta_x;
	}
	if (check_horizontal_wall(player->position, movement_direction, map) == no_wall)
	{
		if (movement_direction.y > 0)
			player->position.y += delta_y;
		else
			player->position.y -= delta_y;
	}
}

int	move_player(int keycode, t_data *cub)
{
	t_vector	movement_direction;

	if (keycode == KEY_W)
		movement_direction = cub->player.direction;
	else if (keycode == KEY_A)
		movement_direction = rotate_vector(cub->player.direction, -(M_PI / 2));
	else if (keycode == KEY_S)
		movement_direction = rotate_vector(cub->player.direction, M_PI);
	else
		movement_direction = rotate_vector(cub->player.direction, M_PI / 2);
	move(movement_direction, &cub->player, cub->map);
	ft_draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->sheet.img, 0, 0);
	return (0);
}
