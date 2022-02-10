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
