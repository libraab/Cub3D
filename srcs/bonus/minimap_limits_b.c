#include "../../headers/cub3d.h"

void	center_on_player(t_player player, int *minimap_boundaries)
{
	minimap_boundaries[up] = (int)player.pos.y - 7;
	minimap_boundaries[down] = (int)player.pos.y + 7;
	minimap_boundaries[left] = (int)player.pos.x - 7;
	minimap_boundaries[right] = (int)player.pos.x + 7;
}

void	protect_out_of_map_limits(t_data *cub, int *minimap_boundaries)
{
	if (minimap_boundaries[up] < 0)
	{
		minimap_boundaries[down] += (minimap_boundaries[up] * -1);
		minimap_boundaries[up] = 0;
	}
	if (minimap_boundaries[down] > cub->map_height)
	{
		minimap_boundaries[up] -= (minimap_boundaries[down] - cub->map_height);
		minimap_boundaries[down] = cub->map_height;
	}
	if (minimap_boundaries[left] < 0)
	{
		minimap_boundaries[right] += (minimap_boundaries[left] * -1);
		minimap_boundaries[left] = 0;
	}
	else if (minimap_boundaries[right] > cub->map_width)
	{
		minimap_boundaries[left] -= (minimap_boundaries[right] - \
				cub->map_width);
		minimap_boundaries[right] = cub->map_width;
	}
}

void	protect_map_too_small(t_data *cub, int *minimap_boundaries)
{
	if (cub->map_height < 15 && cub->map_width >= 15)
	{
		minimap_boundaries[up] = 0;
		minimap_boundaries[down] = get_map_height(cub->map.map);
	}
	if (cub->map_height >= 15 && cub->map_width < 15)
	{
		minimap_boundaries[left] = 0;
		minimap_boundaries[right] = get_map_width(cub->map.map);
	}
	if (cub->map_height < 15 && cub->map_width < 15)
	{
		minimap_boundaries[up] = 0;
		minimap_boundaries[down] = get_map_height(cub->map.map);
		minimap_boundaries[left] = 0;
		minimap_boundaries[right] = get_map_width(cub->map.map);
	}
}

void	ft_get_minimap_boundaries(t_data *cub, int *minimap_boundaries)
{
	center_on_player(cub->player, &minimap_boundaries[0]);
	protect_out_of_map_limits(cub, &minimap_boundaries[0]);
	protect_map_too_small(cub, &minimap_boundaries[0]);
}
