#include "../headers/cub3d.h"

float	calc_step_x(t_vector ray_direction, float x_component)
{
	float	step;

//	printf("x direction: %f   ", ray_direction.x);
	if (ray_direction.x != 0)
		step = x_component * sqrt(1 + (ray_direction.y * ray_direction.y) / (ray_direction.x * ray_direction.x));
	else
		step = FLT_MAX;
//	printf("x step: %f\n", step);
	return (step);
}

float	calc_step_y(t_vector ray_direction, float y_component)
{
	float	step;

//	printf("y direction: %f   ", ray_direction.y);
	if (ray_direction.y != 0)
		step = y_component * sqrt(1 + (ray_direction.x * ray_direction.x) / (ray_direction.y * ray_direction.y));
	else
		step = FLT_MAX;
//	printf("y step: %f\n", step);
	return (step);
}

float	distance_to_x_axis(int on_x, t_coordinates position, t_vector direction)
{
	float	offset;
	float	first_step;

	(void)on_x;
	if (position.x == floor(position.x))
		offset = 1;
	else if (direction.y == 0)
		return (FLT_MAX);
	else if (direction.y < 0)
		offset = position.y - floor(position.y);
	else
		offset = ceil(position.y) - position.y;
	first_step = calc_step_y(direction, offset);
	return (first_step);
}

float	distance_to_y_axis(int on_y, t_coordinates position, t_vector direction)
{
	float	offset;
	float	first_step;

	(void)on_y;
	if (position.y == floor(position.y))
		offset = 1;
	else if (direction.x == 0)
		return (FLT_MAX);
	else if (direction.x < 0)
		offset = position.x - floor(position.x);
	else
		offset = ceil(position.x) - position.x;
	first_step = calc_step_x(direction, offset);
	return (first_step);
}

void	cast_ray(t_ray ray[WIN_WIDTH], t_player player)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
//		printf("ray %d: ", i);
		if (i == 0)
			ray[i].direction = rotate_vector(player.direction, -(FOV / 2));
		else if (i != WIN_WIDTH / 2)
			ray[i].direction = rotate_vector(ray[i - 1].direction, ANGLE_PER_PIXEL);
		else
			ray[i].direction = player.direction;
		ray[i].current_coordinates.x = player.position.x;
		ray[i].current_coordinates.y = player.position.y;
		ray[i].on_y = 0;
		if (player.position.x == floor(player.position.x))
			ray[i].on_y = 1;
		ray[i].on_x = 0;
		if (player.position.y == floor(player.position.y))
			ray[i].on_x = 1;
		ray[i].step_x = calc_step_x(ray[i].direction, 1);
		ray[i].step_y = calc_step_y(ray[i].direction, 1);
		ray[i].travelled_distance = 0;
		//printf("direction: %f, %f     calc'd steps: %f, %f\n", ray[i].direction.y, ray[i].direction.x, ray[i].step_x, ray[i].step_y);
		i++;
	}
}

int	in_map(char **map, int x, int y)
{
	if (x >= 0 && y >= 0 && y < get_map_height(map) && x < (int)ft_strlen(map[y]))
		return (1);
	return (0);
}

int	ray_ver_wall(t_coordinates position, t_vector direction, char **map)
{
	int	coord_x;
	int	coord_y;

	coord_x = (int)position.x;
	coord_y = (int)position.y;
//	printf("in vertical check coordinates: %d, %d\n", coord_x, coord_y);
//	printf("ray direction: %f, %f\n", direction.x, direction.y);
	if (!in_map(map, coord_x, coord_y))
	{
		printf("out of bounds\n");
		sleep(1);
		return (no_wall);
	}
	if (direction.x <= 0 && in_map(map, coord_x - 1, coord_y))
	{
		if (map[coord_y][coord_x - 1] == '1')
			return (wall_left);
	}
	else if (direction.x >= 0 && in_map(map, coord_x, coord_y))
	{
		 if (map[coord_y][coord_x] == '1')
			return (wall_right);
	}
	return (no_wall);
}

int	ray_hor_wall(t_coordinates position, t_vector direction, char **map)
{
	int	coord_x;
	int	coord_y;

	coord_x = (int)position.x;
	coord_y = (int)position.y;
//	printf("in horizontal check coordinates: %d, %d\n", coord_x, coord_y);
//	printf("ray direction: %f, %f\n", direction.x, direction.y);
	if (!in_map(map, coord_x, coord_y))
	{
		sleep(1);
		printf("out of bounds\n");
		return (no_wall);
	}
	if (direction.y <= 0 && in_map(map, coord_x, coord_y - 1))
	{
		if (map[coord_y - 1][coord_x] == '1')
			return (wall_above);
	}
	else if (direction.y >= 0 && in_map(map, coord_x, coord_y))
	{
		if (map[coord_y][coord_x] == '1')
			return (wall_below);
	}
	return (no_wall);
}

void	dda_algorithm(t_player player, t_ray *ray, char **map)
{
	int		wall_hit;
	int		number_of_steps_x;
	int		number_of_steps_y;
	float	initial_distance_to_y;
	float	initial_distance_to_x;

	initial_distance_to_x = distance_to_x_axis(ray->on_x, ray->current_coordinates, ray->direction);
	initial_distance_to_y = distance_to_y_axis(ray->on_y, ray->current_coordinates, ray->direction);
	number_of_steps_x = 0;
	number_of_steps_y = 0;
	wall_hit = no_wall;
	while (wall_hit == no_wall)
	{
		if (initial_distance_to_y + number_of_steps_x * ray->step_x < initial_distance_to_x + number_of_steps_y * ray->step_y)
		{
			ray->travelled_distance = initial_distance_to_y + number_of_steps_x * ray->step_x;
			ray->current_coordinates.x = player.position.x + ray->travelled_distance * ray->direction.x;
			ray->current_coordinates.y = player.position.y + ray->travelled_distance * ray->direction.y;
			wall_hit = ray_ver_wall(ray->current_coordinates, ray->direction, map);
			number_of_steps_x++;
		}
		else
		{
			ray->travelled_distance = initial_distance_to_x + number_of_steps_y * ray->step_y;
			ray->current_coordinates.x = player.position.x + ray->travelled_distance * ray->direction.x;
			ray->current_coordinates.y = player.position.y + ray->travelled_distance * ray->direction.y;
			wall_hit = ray_hor_wall(ray->current_coordinates, ray->direction, map);
			number_of_steps_y++;
		}
	}
}

int	start_dda(t_data *cub)
{
//	printf("player position: %f, %f   ray 450 step: %f, %f   ray 450 direction: %f, %f\n", cub->player.position.x, cub->player.position.y, cub->ray[450].step_x, cub->ray[450].step_y, cub->ray[450].direction.x, cub->ray[450].direction.y);
		dda_algorithm(cub->player, &cub->ray[450], cub->map);
		ft_put_img2(&cub->sheet, DEEP_PINK, cub->ray[450].current_coordinates.y * 10, cub->ray[450].current_coordinates.x * 10);
	/*int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{ 
		dda_algorithm(cub->player, &cub->ray[i], cub->map);
		ft_put_img2(&cub->sheet, DEEP_PINK, (cub->ray[i].current_coordinates.y * 10), cub->ray[i].current_coordinates.x * 10);
		i++;
	}*/
	return (0);
}
