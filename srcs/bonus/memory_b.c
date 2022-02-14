/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 04:23:24 by abouhlel          #+#    #+#             */
/*   Updated: 2022/02/14 04:23:25 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

void	ft_free_double(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_free(&tab[i]);
		i++;
	}
	free (tab);
}
