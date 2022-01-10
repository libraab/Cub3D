/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:50:28 by abouhlel          #+#    #+#             */
/*   Updated: 2021/09/08 21:58:24 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "mlx.h"
# include "../libft/libft.h"
# include "../header/mlx_keycode.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_data
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_sprite
{
	void	*img;
	int		wi;
	int		he;
}	t_sprite;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_main
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			step;
	t_pos		p_pos;
	t_sprite	ground;
	t_sprite	wall;
	t_sprite	exit;
	t_sprite	exit2;
	t_sprite	p_up;
	t_sprite	p_down;
	t_sprite	p_l;
	t_sprite	p_l2;
	t_sprite	p_r;
	t_sprite	p_r2;
	t_sprite	map_img;
	int			linelen;
	int			one_p;
	int			all_step;
	char		**map;
	int			victory;
	int			state_pose;
}				t_main;


#endif
