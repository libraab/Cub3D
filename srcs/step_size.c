
void	calc_deltas(t_vector direction, float *delta_x, float *delta_y, float distance)
{
	float		step_x;
	float		step_y;

	step_x = calc_step_x(direction, TILE_SIZE);
	step_y = calc_step_y(direction, TILE_SIZE);
	*delta_x = distance / step_x;
	*delta_y = distance / step_y;
}
void	move(t_vector movement_direction, t_player *player, char **map)
{
	float		delta_x;
	float		delta_y;

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
	printf("The player moved by %f pixel on x and %f px on y\n", delta_x, delta_y);
}

void	first_step(t_ray *ray)
{
	if (distance_to_x_axis(ray->on_x, ray->current_coordinates, ray->direction) < distance_to_y_axis(ray->on_y, ray->current_coordinates, ray->direction))
	{
		ray->travelled_distance += distance_to_x_axis(ray->on_x, ray->current_coordinates, ray->direction);
		if (ray->direction.y < 0)
			ray->current_coordinates.y = floor(ray->current_coordinates.y);
		else
			ray->current_coordinates.y = ceil(ray->current_coordinates.y);
		ray->on_x = 1;
	}
	else if (distance_to_y_axis(ray->on_y, ray->current_coordinates, ray->direction) < distance_to_x_axis(ray->on_x, ray->current_coordinates, ray->direction))
	{
		ray->travelled_distance += distance_to_y_axis(ray->on_y, ray->current_coordinates, ray->direction);
		if (ray->direction.x < 0)
			ray->current_coordinates.x = floor(ray->current_coordinates.x);
		else
			ray->current_coordinates.x = ceil(ray->current_coordinates.x);
		ray->on_y = 1;
	}
	ray->step_x = calc_step_x(ray->direction, TILE_SIZE);
	ray->step_y = calc_step_y(ray->direction, TILE_SIZE);
}

float	calc_step_x(t_vector ray_direction, float x_component)
{
	float	step;

	if (ray_direction.x != 0)
		step = x_component * sqrt(1 + (ray_direction.y * ray_direction.y) / (ray_direction.x * ray_direction.x));
	else
		step = FLT_MAX;
	printf("step for 1 x unit: %f\n", step);
	return (step);
}

float	calc_step_y(t_vector ray_direction, float y_component)
{
	float	step;

	if (ray_direction.y != 0)
		step = y_component * sqrt(1 + (ray_direction.x * ray_direction.x) / (ray_direction.y * ray_direction.y));
	else
		step = FLT_MAX;
	printf("step for 1 y unit: %f\n", step);
	return (step);
}

float	distance_to_x_axis(int on_x, t_vector position, t_vector direction)
{
	float	offset;
	float	first_step;

	if (on_x == 1)
		return (0);
	else if (direction.y == 0)
		return (FLT_MAX);
	else if (direction.y > 0)
		offset = ceil(position.y) - position.y;
	else
		offset = position.y - floor(position.y);
	first_step = calc_step_y(direction, offset);
	printf("distance to x: %f\n", first_step);
	return (first_step);
}

float	distance_to_y_axis(int on_y, t_vector position, t_vector direction)
{
	float	offset;
	float	first_step;

	if (on_y == 1)
		return (0);
	else if (direction.x == 0)
		return (FLT_MAX);
	else if (direction.x > 0)
		offset = ceil(position.x) - position.x;
	else
		offset = position.x - floor(position.x);
	first_step = calc_step_x(direction, offset);
	printf("distance to y: %f\n", first_step);
	return (first_step);
}
