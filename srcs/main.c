/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:18:11 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/17 14:11:37 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	ft_get_height(char *file)
{
	int		fd;
	int		i;
	char	*line;

	i = ft_strlen(file) - 1;
	if (file[i] != 'b' && file[i - 1] != 'u'
		&& file[i - 2] != 'c'
		&& file[i - 3] != '.')
		ft_error(1);
	fd = open(file, O_DIRECTORY);
	if (fd != -1)
		ft_error(2);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(7);
	i = 0;
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
		ft_error(0);
	cub.map = ft_calloc(sizeof(char *), ft_get_height(av[1]) + 1);
	ft_parse(&cub, av);
	ft_free_double(cub.tex);
	ft_free_double(cub.map);
	return (0);
}
