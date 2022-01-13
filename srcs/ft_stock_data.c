/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:29:20 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/13 18:05:12 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	ft_init_data(t_data *cub)
{
	cub->map = NULL;
}

void	ft_stock_map(t_data *cub, char *file)
{
	int		i;
	int		fd;
	int		ret;
	char	*line;

	i = 0;
	ret = 1;
	fd = open(file, O_RDONLY);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (line[0] == 'N' || line[0] == 'S'
			|| line[0] == 'E' || line[0] == 'W'
			|| line[0] == 'F' || line[0] == 'C'
			|| line[0] == '\n' || line[0] == '\0')
		{
			free (line);
			continue ;
		}
		cub->map[i++] = ft_strdup(line);
		free (line);
	}
	close (fd);
	//******************************************************
	printf("* * * M A P * * * \n");
	printf("------------------\n\n");
	for (int i = 0; cub->map[i]; i++)
		printf("[%s]\n", cub->map[i]);
	printf("\n------------------\n");
	//******************************************************
}
