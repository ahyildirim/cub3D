#include "../../includes/cub3d.h"

void	free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
}

void free_map(t_data *data)
{
	if (data->map->map_array)
		free_arr(data->map->map_array);
	free(data->map);
}

void free_textures(t_data *data)
{
	int i;
	
	if (!data || !data->texture.xpm)
		return;
	i = -1;
	while (++i < 4)
	{
		if (data->texture.xpm[i])
		{
			if (data->texture.xpm[i]->img_ptr)
				mlx_destroy_image(data->mlx_ptr, data->texture.xpm[i]->img_ptr);
			free(data->texture.xpm[i]);
		}
	}
}

void free_img(t_data *data)
{
	if (data->img)
	{
		if (data->img->img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
		free(data->img);
	}
}

void free_data(t_data *data)
{
	if (!data)
		return;
	free_map(data);
	if (data->player)
		free(data->player);
	free_img(data);
	free_textures(data);
	if (data->mlx_ptr)
	{
		if (data->win_ptr)
		{
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
			data->win_ptr = NULL;
		}
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
	free(data);
}