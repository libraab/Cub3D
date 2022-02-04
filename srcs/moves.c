#include "../headers/cub3d.h"

void	move(t_vector movement_direction, t_player *player, char **map)
{
	if (check_vertical_wall(player->position, movement_direction, map) == no_wall)
		player->position.x += movement_direction.x * PLAYER_STEP;
	if (check_horizontal_wall(player->position, movement_direction, map) == no_wall)
		player->position.y += movement_direction.y * PLAYER_STEP;
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
