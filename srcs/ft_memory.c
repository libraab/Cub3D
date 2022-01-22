/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:01:52 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/22 17:04:38 by bleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
