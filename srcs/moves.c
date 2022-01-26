#include "../headers/cub3d.h"

void	calc_axes_moves(t_vector movement_direction, float *x_move, float *y_move)
{
	float		step_x;
	float		step_y;

	step_x = calc_step_x(movement_direction, 1);
	step_y = calc_step_y(movement_direction, 1);
	*x_move = PLAYER_STEP / step_x;
	*y_move = PLAYER_STEP / step_y;
}

void	move_forward(t_player *player)
{
	t_vector	movement_direction;
	float		x_move;
	float		y_move;

	movement_direction = player->direction;
	calc_axes_moves(movement_direction, &x_move, &y_move);
	if (movement_direction.x > 0)
		player->position.x += x_move;
	else
		player->position.x -= x_move;
	if (movement_direction.y > 0)
		player->position.y += y_move;
	else
		player->position.y -= y_move;
}

void	move_left(t_player *player)
{
	t_vector	movement_direction;
	float		x_move;
	float		y_move;

		movement_direction = rotate_vector(player->direction, -(M_PI / 2));
		calc_axes_moves(movement_direction, &x_move, &y_move);
		if (movement_direction.x > 0)
			player->position.x += x_move;
		else
			player->position.x -= x_move;
		if (movement_direction.y > 0)
			player->position.y += y_move;
		else
			player->position.y -= y_move;
}

void	move_right(t_player *player)
{
	t_vector	movement_direction;
	float		x_move;
	float		y_move;

		movement_direction = rotate_vector(player->direction, M_PI / 2);
		calc_axes_moves(movement_direction, &x_move, &y_move);
		if (movement_direction.x > 0)
			player->position.x += x_move;
		else
			player->position.x -= x_move;
		if (movement_direction.y > 0)
			player->position.y += y_move;
		else
			player->position.y -= y_move;
}

void	move_back(t_player *player)
{
	t_vector	movement_direction;
	float		x_move;
	float		y_move;

		movement_direction = rotate_vector(player->direction, M_PI);
		calc_axes_moves(movement_direction, &x_move, &y_move);
		if (movement_direction.x > 0)
			player->position.x += x_move;
		else
			player->position.x -= x_move;
		if (movement_direction.y > 0)
			player->position.y += y_move;
		else
			player->position.y -= y_move;
}

int	move_player(int keycode, t_data *cub)
{
	if (keycode == KEY_W)
		move_forward(&cub->player);
	else if (keycode == KEY_A)
		move_left(&cub->player);
	else if (keycode == KEY_S)
		move_back(&cub->player);
	else if (keycode == KEY_D)
		move_right(&cub->player);
	mlx_pixel_put(cub->mlx_ptr, cub->win_ptr, cub->player.position.x, cub->player.position.y, DEEP_PINK);
	return (0);
}
