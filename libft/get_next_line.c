/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:46:37 by abouhlel          #+#    #+#             */
/*   Updated: 2022/01/13 11:46:39 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_eco(char **join, int *size_read, char buffer[BUFFER_SIZE], int fd)
{
	char	*tmp;

	*size_read = 1;
	if (*join == 0)
		*join = ft_calloc(sizeof(char), 1);
	while (ft_strchr(*join, '\n') == 0 && *size_read > 0)
	{
		*size_read = read(fd, buffer, BUFFER_SIZE);
		buffer[*size_read] = 0;
		tmp = ft_strjoin(*join, buffer);
		free(*join);
		*join = tmp;
	}
}

int	get_next_line(int fd, char **line)
{
	int			size_read;
	char		buffer[BUFFER_SIZE + 1];
	static char	*join = 0;
	char		*tmp;

	ft_eco(&join, &size_read, buffer, fd);
	if (size_read == 0)
	{
		*line = ft_strdup(join);
		free(join);
		join = 0;
		return (0);
	}
	if (size_read > 0)
	{
		*line = ft_substr(join, 0, (ft_strchr(join, '\n') - join));
		tmp = ft_strdup(join + ft_strlen(*line) + 1);
		free(join);
		join = tmp;
		return (1);
	}
	if (fd == -1 && BUFFER_SIZE > 0)
		free(join);
	return (-1);
}
