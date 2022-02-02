/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:50:28 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/01 17:09:57 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../headers/mlx_keycode.h"
# include "../libft/libft.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <float.h>

# define WIN_WIDTH 900
# define WIN_HEIGHT 600
# define TILE_SIZE 50
# define FOV (4 * M_PI) / 9
# define ANGLE_PER_PIXEL FOV / WIN_WIDTH
# define ROTATION_ANGLE M_PI / 12 
# define PLAYER_STEP 25 

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define GOLD 0xFFD700
# define DEEP_PINK 0xFF1493

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
	wall_above,
	wall_right,
	wall_below,
	wall_left
};

typedef struct s_vector
{
	float	x;
	float	y;
}			t_vector;

typedef struct s_coordinates
{
	int	x;
	int	y;
}			t_coordinates;

typedef struct s_info
{
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}			t_info;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}			t_img;

typedef struct s_player
{
	t_coordinates	position;
	t_vector		direction;
	t_img			img;
}					t_player;

typedef struct s_ray
{
	t_vector		direction;
	t_coordinates	current_coordinates;
	float			travelled_distance;
	float			step_x;
	float			step_y;
	int				on_x;
	int				on_y;
}					t_ray;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	char		**tex;
	t_img		wall;
	t_img		sheet;
	t_img		frame;
	t_img		north_wall;
	int			floor;
	int			ceiling;
	int			mouse_x;
	t_player	player;
	t_ray		rays[WIN_WIDTH];
}				t_data;

//======================================================//
//				* C H E C K _ T E X T U R E S *			//
//======================================================//
int				ft_skip_spaces(char *str, int i, int reverse);
int				ft_end_of_texture(char *line);
void			ft_valid_texture_file(char *str);
void			ft_check_fc(t_data *cub);
void			ft_valid_texture(t_data *cub);
//======================================================//
//				* C H E C K _ W A L L S *				//
//======================================================//
int				ft_north_wall(char **map, int i, int j);
int				ft_south_wall(char **map, int i, int j);
int				ft_east_wall(char **map, int i, int j);
int				ft_west_wall(char **map, int i, int j);
//======================================================//
//					* D E F I N E _ I M G *				//
//======================================================//
void			ft_define_img(t_data *cub);
void			ft_pixel_put(t_info *data, int x, int y, int color);
unsigned int	ft_pixel_get(t_info *data, int x, int y);
void			ft_put_img(t_img *dest, t_img *src, float x, float y);
void			ft_put_img2(t_img *dest, int color, int x, int y);
//======================================================//
//						* D R A W *						//
//======================================================//
void			ft_print_all(t_data *cub);
void			draw_fov(t_ray rays[WIN_WIDTH], t_data *cub, int colour);
void			draw_floor(t_data *cub);
void			draw_ceiling(t_data *cub);
//======================================================//
//						* E R R O R S *					//
//======================================================//
void			ft_error(int x);
//======================================================//
//						* H O O K S *					//
//======================================================//
int				ft_exit(void);
int				key_release(int keycode);
int				rotate_player(int keycode, t_data *cub);
int				player_movement(int keycode, t_data *cub);
int				mouse_move(int x, int y, t_data *cub);
//======================================================//
//						* M A I N *						//
//======================================================//
int				ft_get_height(char *file);
//======================================================//
//						* M A T H *						//
//======================================================//
float			calc_step_x(t_vector ray_direction, float x_component);
float			calc_step_y(t_vector ray_direction, float y_component);
float			distance_to_y_axis(int on_y, t_coordinates position, t_vector direction);
float			distance_to_x_axis(int on_x, t_coordinates position, t_vector direction);
t_vector		starting_direction(char player_character);
t_vector		rotate_vector(t_vector to_rotate, float angle);
void			cast_rays(t_ray rays[WIN_WIDTH], t_player player);
//======================================================//
//						* M E M O R Y *					//
//======================================================//
void			ft_free(char **str);
void			ft_free_double(char **tab);
//======================================================//
//						* M I N I _ M A P *				//
//======================================================//
void			ft_update_map(t_data *cub, int x, int y);
void			ft_draw_frame(t_data *cub);
void			ft_draw_minimap(t_data *cub);
//======================================================//
//						* M O V E S *					//
//======================================================//
void			calc_deltas(t_vector movement_direction, float *delta_x, float *delta_y, float distance);
void			move_forward(t_player *player, char **map);
void			move_left(t_player *player, char **map);
void			move_right(t_player *player, char **map);
void			move_back(t_player *player, char **map);
int				move_player(int keycode, t_data *cub);
int				check_horizontal_wall(t_coordinates position, t_vector direction, char **map);
int				check_vertical_wall(t_coordinates position, t_vector direction, char **map);
//======================================================//
//						* P A R S I N G *				//
//======================================================//
void			ft_valid_chars(t_data *cub);
void			ft_valid_walls(t_data *cub);
void			ft_check_double_texture(t_data *cub, int i, int e);
int				get_surface(char *surface);
void			ft_check_digits(char *str);
//======================================================//
//				* S T O C K * D A T A *					//
//======================================================//
void			ft_init_img(t_img *img);
t_player		init_player(char **map);
void			ft_init_data(t_data *cub, char **av);
void			ft_stock_map(t_data *cub, char *file);
void			ft_stock_texture(t_data *cub, char *file);
//======================================================//
//				* U T I L S *							//
//======================================================//
int				ft_is_direction(char c);
int				create_rgb(int r, int g, int b);
int				ft_tablen(char **str);
int				ft_tabwidth(char **str);
//======================================================//
//					* F U N C T I O N S *				//
//======================================================//
int				start_dda(t_data *cub);
void			print_green_dot(t_data *cub, int x, int y);
int				is_inside_map(char c);
void			ft_print_texture(t_data *cub, int x);
#endif
