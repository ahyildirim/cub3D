#include "../../includes/cub3d.h"

void	free_arr(void **arr)
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

static void	free_map(t_data *data)
{
	if (data->map)
		free_arr((void **)data->map);
}

static void free_textures(t_data *data)
{
	int i;
	
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

static void free_img(t_data *data)
{
	if (data->img)
	{
		if (data->img->img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
		free(data->img);
	}
}

int free_data(t_data *data)
{
	if (!data)
		return (0);
	free_map(data);
	if (data->player)
		free(data->player);
	free_img(data);
	free_textures(data);
	if (data->mlx_ptr)
	{
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		// mlx_destroy_display(data->mlx_ptr);  // Linux'ta gerekli
		free(data->mlx_ptr);
	}
	free(data);
	return (0);
}