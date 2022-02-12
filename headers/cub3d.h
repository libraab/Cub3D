/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:50:28 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/12 03:33:52 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../headers/mlx_keycode.h"
# include "../libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <float.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 760
# define TILE_SIZE 64
# define FOV 66
# define PLAYER_SPEED 0.3

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum
{
	no_wall,
	east_wall,
	north_wall,
	south_wall,
	west_wall
};

enum
{
	left,
	right,
	up,
	down
};

typedef struct s_vector
{
	float	x;
	float	y;
}			t_vector;

typedef struct s_info
{
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}			t_info;

typedef struct s_img
{
	int		height;
	int		width;
	t_info	info;
	void	*img;
}			t_img;

typedef struct s_player
{
	t_img			img;
	t_vector		direction;
	t_vector		pos;
}					t_player;

typedef struct s_ray
{
	float			distance;
	float			step_x;
	float			step_y;
	int				wall_hit;
	t_vector		direction;
	t_vector		impact;
}					t_ray;

typedef struct s_map
{
	char	**map;
	int		x;
	int		y;
}			t_map;

typedef struct s_walls
{
	t_img	east;
	t_img	north;
	t_img	south;
	t_img	west;
}			t_walls;

typedef struct s_data
{
	char		**minimap;
	char		**tex;
	int			ceiling;
	int			floor;
	int			map_height;
	int			map_width;
	int			mouse_x;
	t_img		frame;
	t_img		mini_wall;
	t_img		sheet;
	t_map		map;
	t_player	player;
	t_ray		ray[WIN_WIDTH];
	t_walls		walls;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_data;

//============================================================================//
//						* C H E C K _ T E X T U R E S *						  //
//============================================================================//
int				ft_skip_spaces(char *str, int i, int reverse);
int				ft_end_of_texture(char *line);
void			ft_valid_texture_file(char *str);
void			ft_check_floor_ceiling(t_data *cub);
void			ft_valid_texture(t_data *cub);
//============================================================================//
//						* C H E C K _ W A L L S *							  //
//============================================================================//
int				ft_north_wall(char **map, int i, int j);
int				ft_south_wall(char **map, int i, int j);
int				ft_east_wall(char **map, int i, int j);
int				ft_west_wall(char **map, int i, int j);
//============================================================================//
//								* D D A *									  //
//============================================================================//
float			ride_along_x(t_ray *ray, t_map *map, float *travelled_on_x);
float			ride_along_y(t_ray *ray, t_map *map, float *travelled_on_y);
void			get_impact_coordinates(t_ray *ray, t_vector player_position);
int				dda_algorithm(t_player player, t_ray *ray, t_map map);
int				start_dda(t_data *cub);
//============================================================================//
//							* D E F I N E _ I M G *							  //
//============================================================================//
void			get_minimap_images(t_data *cub);
void			ft_pixel_put(t_info *data, int x, int y, int color);
unsigned int	ft_pixel_get(t_info *data, int x, int y);
void			ft_put_img(t_img *dest, t_img *src, int x, int y);
void			ft_put_img2(t_img *dest, int color, int x, int y);
//============================================================================//
//							* D I S T A N C E *								  //
//============================================================================//
float			calc_dist_to_screen(void);
float			calc_wall_height(float distance_to_wall, float angle);
float			get_wall_height(float distance, int ray_number);
//============================================================================//
//								* D R A W *									  //
//============================================================================//
void			draw_floor(t_data *cub);
void			draw_ceiling(t_data *cub);
//============================================================================//
//								* E R R O R S *								  //
//============================================================================//
void			ft_error(int x);
int				ft_exit(void);
//============================================================================//
//								* H O O K S *								  //
//============================================================================//
int				key_release(int keycode);
int				rotation_key(int keycode);
int				movement_key(int keycode);
int				player_movement(int keycode, t_data *cub);
//============================================================================//
//							* I N I T _ D A T A *							  //
//============================================================================//
t_player		init_player(char **map);
void			ft_init_data(t_data *cub, char **av);
//============================================================================//
//							* M A P _ U T I L S *							  //
//============================================================================//
int				ft_get_height(char *file);
int				get_map_height(char **tab);
int				get_map_width(char **map);
//============================================================================//
//								* M E M O R Y *								  //
//============================================================================//
void			ft_free(char **str);
void			ft_free_double(char **tab);
//============================================================================//
//							* M I N I _ M A P *								  //
//============================================================================//
void			ft_draw_frame(t_data *cub);
void			fill_minimap_characters(t_data *cub, int *boundaries, int i);
void			ft_stock_minimap(t_data *cub, int *tab);
void			ft_print_minimap(t_data *cub);
void			ft_draw_minimap(t_data *cub);
//============================================================================//
//						* M I N I _ M A P _ L I M I T S *					  //
//============================================================================//
void			center_on_player(t_player player, int *minimap_boundaries);
void			protect_out_of_map_limits(t_data *cub, int *minimap_boundaries);
void			protect_map_too_small(t_data *cub, int *minimap_boundaries);
void			ft_get_minimap_boundaries(t_data *cub, int *minimap_boundaries);
//============================================================================//
//								* M O V E S *								  //
//============================================================================//
int				check_horizontal_wall(t_vector pos, t_vector dir, char **map);
int				check_vertical_wall(t_vector pos, t_vector dir, char **map);
void			move(t_vector mov_direction, t_player *player, char **map);
int				move_player(int keycode, t_data *cub);
//============================================================================//
//							* P A R S I N G *								  //
//============================================================================//
void			ft_valid_chars(t_data *cub);
void			ft_valid_walls(t_data *cub);
void			ft_check_double_texture(t_data *cub, int i, int e);
int				get_surface(char *surface);
void			ft_check_digits(char *str);
//============================================================================//
//					* P R I N T _ T E X T U R E *							  //
//============================================================================//
void			print_north_wall(t_data *cub, int wall_height, \
				int column, float ratio_x);
void			print_south_wall(t_data *cub, int wall_height, \
				int column, float ratio_x);
void			print_east_wall(t_data *cub, int wall_height, \
				int column, float ratio_y);
void			print_west_wall(t_data *cub, int wall_height, \
				int column, float ratio_y);
void			ft_print_texture(t_data *cub, int height, int type, int column);
//============================================================================//
//						*  R A Y C A S T I N G  *							  //
//============================================================================//
float			calc_step_x(t_vector ray_direction, float x_component);
float			calc_step_y(t_vector ray_direction, float y_component);
float			distance_to_x_axis(t_vector position, t_vector direction);
float			distance_to_y_axis(t_vector position, t_vector direction);
void			cast_ray(t_ray ray[WIN_WIDTH], t_player player);
//============================================================================//
//						* R O T A T I O N S *								  //
//============================================================================//
int				rotate_player(int keycode, t_data *cub);
t_vector		rotate_vector(t_vector to_rotate, float angle);
//============================================================================//
//						* S T O C K _ D A T A *								  //
//============================================================================//
void			stock_map(t_data *cub, int fd);
void			ft_get_map(t_data *cub, char *file);
void			get_wall_textures(t_data *cub, char *name, t_walls *walls);
void			stock_texture(t_data *cub, int fd);
void			ft_get_texture(t_data *cub, char *file);
//============================================================================//
//								* U T I L S *								  //
//============================================================================//
int				ft_is_direction(char c);
int				create_rgb(int r, int g, int b);
void			fill_blanks(char **map);
t_vector		starting_direction(char player_character);
//============================================================================//
//							* W A L L _ H E I G H T *						  //
//============================================================================//
float			calc_dist_to_screen(void);
float			calc_wall_height(float distance_to_wall, float angle);
float			get_wall_height(float distance, int ray_number);
//============================================================================//
//						* W A L L _ T E X T U R E S *						  //
//============================================================================//
void			north_wall_texture(t_data *cub, char *name, t_walls *walls);
void			south_wall_texture(t_data *cub, char *name, t_walls *walls);
void			east_wall_texture(t_data *cub, char *name, t_walls *walls);
void			west_wall_texture(t_data *cub, char *name, t_walls *walls);

#endif
