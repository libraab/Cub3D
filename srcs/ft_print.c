/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:17:19 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/17 14:12:17 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_print_map(t_data *cub)
{
	int	i;

	i = 0;
	printf("* * * M A P * * * \n");
	printf("-----------------------------------------\n");
	while (cub->map[i])
	{
		printf("[%s]\n", cub->map[i]);
		i++;
	}
	printf("---------------------------------------\n");
}

void	ft_print_texture(t_data *cub)
{
	int	i;

	i = 0;
	printf("\n* * * T E X T U R E S * * * \n");
	printf("----------------------------------\n");
	while (cub->tex[i])
	{
		printf("[%s]\n", cub->tex[i]);
		i++;
	}
	printf("----------------------------------\n");
}
