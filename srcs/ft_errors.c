/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:27:51 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/13 15:37:51 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_error(t_data *cub, int x)
{
	if (x == 0)
		write(2, "Error : Wrong argument number\n", 30);
	if (x == 1)
		write(2, "Error : Wrong extention\n", 24);
	if (x == 2)
		write(2, "Error : This is a directory\n", 28);
	if (x == 3)
		write(2, "Error : Invalid char\n", 21);
	if (x == 4)
		write(2, "Error : No direction\n", 21);
	if (x == 5)
		write(2, "Error : Only one direction\n", 27);
	if (x == 6)
		write(2, "Error : Hole in the wall\n", 25);
	//ft_free_double(cub.map);
	(void) cub;
	exit(EXIT_FAILURE);
}