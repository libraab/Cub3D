/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:18:11 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/13 14:46:44 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	ft_get_height(char *file)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		i++;
		free(line);
	}
	i++;
	free(line);
	close (fd);
	return (i);
}

int	main(int ac, char **av)
{
	t_data	cub;

	ft_init_data(&cub);
	if (ac < 2 || ac > 2)
		ft_error(&cub, 0);
	cub.map = ft_calloc(sizeof(char *), ft_get_height(av[1]) + 1);
	ft_check_error(&cub, av);
	//if (ft_check_error(cub, av))
		//ft_parse(cub);
	return (0);
}
