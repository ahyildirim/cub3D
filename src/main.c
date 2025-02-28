#include "../includes/cub3d.h"

int	quit_game(t_data *data)
{
    free_data(data);
    exit(0);
	return (1);
}

static int	game_loop(t_data *data)
{
	if (move(data))
		draw(data);
	return (0);
}

int main(int ac, char **argv)
{
    if (ac != 2)
        printf("Please insert a map!");
    t_data *data;

    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (0);
    ft_memset(data, 0, sizeof(t_data));
    if (!initialize(data, argv))
        return (0);
    mlx_loop_hook(data->mlx_ptr, game_loop, data);
	draw(data);
    mlx_loop(data->mlx_ptr);
}
