/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:50:28 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/25 04:21:45 by bleotard         ###   ########.fr       */
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

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900
# define FOV (4 * M_PI) / 9
# define ANGLE_PER_PIXEL FOV / WIN_WIDTH

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define GOLD 0xFFD700

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
	void	*img;
	int		width;
	int		height;
}			t_img;

typedef	struct s_player
{
	t_vector	position;
	t_vector	direction;
	t_img		img;
}				t_player;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	char		**tex;
	t_img		wall_north;
	t_img		wall_south;
	t_img		wall_east;
	t_img		wall_west;
	t_img		mini;
	t_player	player;
}				t_data;

//======================================================//
//						* M A I N *						//
//======================================================//
int		ft_get_height(char *file);
int		ft_exit(void);
//======================================================//
//						* M E M O R Y *					//
//======================================================//
void	ft_free(char **str);
void	ft_free_double(char **tab);
//======================================================//
//						* P A R S I N G *				//
//======================================================//
void	ft_valid_chars(t_data *cub);
void	ft_valid_walls(t_data *cub);
void	ft_check_double_texture(t_data *cub, int i, int j, int e);
void	ft_check_digits(char *str, int j);
void	ft_parse(t_data *cub, char **av);
//======================================================//
//					* T E X T U R E S *					//
//======================================================//
int		ft_skip_spaces(char *str, int i, int reverse);
int		ft_end_of_texture(char *line);
void	ft_valid_texture_file(char *str, int j);
void	ft_check_fc(char **tb, int f, int c);
void	ft_valid_texture(t_data *cub, int i, int j);
//======================================================//
//				* S T O C K * D A T A *					//
//======================================================//
void	ft_init_data(t_data *cub);
void	ft_stock_map(t_data *cub, char *file);
void	ft_stock_texture(t_data *cub, char *file);
//======================================================//
//				* W A L L S *							//
//======================================================//
void	ft_error(int x);
int		ft_north_wall(char **map, int i, int j);
int		ft_south_wall(char **map, int i, int j);
int		ft_east_wall(char **map, int i, int j);
int		ft_west_wall(char **map, int i, int j);
//======================================================//
//					* P R I N T *						//
//======================================================//
void	ft_print_map(t_data *cub);
void	ft_print_texture(t_data *cub);
//======================================================//
//					* P R I N T *						//
//======================================================//
void	ft_draw_pixel(void *mlx_ptr, void *win_ptr, int x, int y, int color);

t_vector	*cast_rays(t_vector direction);
t_vector	starting_direction(char player_character);
t_player	init_player(char **map);

#endif
