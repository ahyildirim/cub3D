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

int free_data(t_data *data)
{
	free_map(data);
	return (0);
}