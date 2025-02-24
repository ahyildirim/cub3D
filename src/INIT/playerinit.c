#include "../../includes/cub3d.h"

static void	set_plane(t_data *data, char player)
{
	if (player == 'N')
	{
		data->player->plane.x = FOV;
		data->player->plane.y = 0;
	}
	else if (player == 'S')
	{
		data->player->plane.x = -FOV;
		data->player->plane.y = 0;
	}
	else if (player == 'W')
	{
		data->player->plane.x = 0;
		data->player->plane.y = -FOV;
	}
	else if (player == 'E')
	{
		data->player->plane.x = 0;
		data->player->plane.y = FOV;
	}
}

static void	set_player_dir(t_data *data, char player)
{
	if (player == 'N')
	{
		data->player->dir.x = 0;
		data->player->dir.y = -1;
	}
	else if (player == 'S')
	{
		data->player->dir.x = 0;
		data->player->dir.y = 1;
	}
	else if (player == 'W')
	{
		data->player->dir.x = -1;
		data->player->dir.y = 0;
	}
	else if (player == 'E')
	{
		data->player->dir.x = 1;
		data->player->dir.y = 0;
	}
	set_plane(data, player);
}

/*
	Mapin içinde gezerek karakterin konumunu yönünü ve düzlemini aldığımız fonksiyon.
	Ayrıca karakter sayısını sayar ve birden fazla ise hata döndürür.
*/

int initialize_player(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->player = (t_player *)malloc(sizeof(t_player));
	data->player->l_rotate = 0;
	data->player->r_rotate = 0;
	while (data->map->map_array[++i])
	{
		j = -1;
		while (data->map->map_array[i][++j])
		{
			if (ft_strchr("NSEW", data->map->map_array[i][j]))
			{
				data->player->pos.x = (double)j + 0.5; //+0.5 olmasının sebebi arraydeki her karakter, 1'e 1 düşünürsek oyuncuyu tam ortadan başlatabilmek için.
				data->player->pos.y = (double)i + 0.5;
				data->map->players++;
				set_player_dir(data, data->map->map_array[i][j]);
			}
		}
	}
	if (data->map->players == 1)
		return (1);
	return (printf("The map cannot contain more than one player!"), 0);
}