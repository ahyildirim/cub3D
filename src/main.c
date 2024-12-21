#include "../includes/cub3d.h"

int	quit_game(t_data *data)
{
	exit(mlx_destroy_window(data->mlx_ptr, data->win_ptr));
	return (1);
}

int	main(int ac, char **argv)
{
	if (ac != 2)
		printf("Please insert a map!");
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!initialize(data, argv))
		return (0);
	mlx_loop(data->mlx_ptr);
}
