#include "../../includes/cub3d.h"

int	error_free(char *msg, t_data *data, int error_mod)
{
	if(error_mod == 0)
	{
		printf("%s", msg);
		if (data->mlx_ptr)
		{
			mlx_destroy_display(data->mlx_ptr);
			free(data->mlx_ptr);
			data->mlx_ptr = NULL;
		}
		free(data->map);
		free(data);
		return (0);
	}
	if (error_mod == 1)
	{
		printf("%s\n", msg);
		if (!data)
			return (0);
		free_map(data);
		free_textures(data);
		if (data->mlx_ptr)
		{
			mlx_destroy_display(data->mlx_ptr);
			free(data->mlx_ptr);
			data->mlx_ptr = NULL;
		}
		free(data);
		return (0);
	}
	return (1);
}
