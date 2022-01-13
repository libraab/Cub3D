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

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	int			map_height;
	int			map_lengh;
}				t_data;

//======================================================//
//						* M A I N *						//
//======================================================//
int		ft_get_height(char *file);
//======================================================//
//						* M E M O R Y *					//
//======================================================//
void	ft_free(char *str);
void	ft_free_double(char **tab);
//======================================================//
//						* P A R S I N G *				//
//======================================================//
int		ft_check_error(t_data *cub, char **av);
void	ft_valid_chars(t_data *cub);
void	ft_valid_file(t_data *cub, char *file);
//======================================================//
//						* E R R O R S *					//
//======================================================//
void	ft_error(t_data *cub, int x);
//======================================================//
//				* S T O C K * D A T A *					//
//======================================================//
void	ft_stock_map(t_data *cub, char *file);
void	ft_init_data(t_data *cub);

#endif
