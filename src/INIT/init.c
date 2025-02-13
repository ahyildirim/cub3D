#include "../../includes/cub3d.h"

static void	init_key_events(t_data *data)
{
	data->onkey.key_w = 0;
	data->onkey.key_a = 0;
	data->onkey.key_s = 0;
	data->onkey.key_d = 0;
	data->onkey.key_up = 0;
	data->onkey.key_down = 0;
	data->onkey.key_left = 0;
	data->onkey.key_right = 0;
}

/*
	Image structını başlat ve doldur.
*/
int initialize_img(t_data *data)
{
	data->img = (t_img *)malloc(sizeof(t_img));
	if (!data->img)
		return (0);
	// Yeni resim oluştur ve img_ptr değişkenine at
	data->img->img_ptr = mlx_new_image(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->img->img_ptr)
		return (0);
	// Data->img->addr değişkenine resmin adresini al.
	data->img->addr = mlx_get_data_addr(data->img->img_ptr, &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);
	if (!data->img->addr)
		return (0);
	
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0, 0);
	return (1);
}

/*
	Haritayı, oyuncuyu, eventleri, mlx hooklarını ve looplarını
	oluşturduğumuz ana fonksiyon.
*/

int initialize(t_data *data, char **av)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	if (!create_map(data, av[1]))
		return (0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!data->win_ptr)
		return (0);
	init_key_events(data);
	data->map->players = 0;
	if (!initialize_player(data))
		return (0);
	if (!initialize_img(data))
		return (0);
	//mlx_loop_hook(data->mlx_ptr, render_frame, data);  // Add this line
	mlx_hook(data->win_ptr, ON_KEYUP, 1L << 1, key_up, data);
	mlx_hook(data->win_ptr, ON_KEYDOWN, 1L << 0, key_down, data);
	mlx_hook(data->win_ptr, ON_DESTROY, 1L << 0, quit_game, data);
	return (1);
}