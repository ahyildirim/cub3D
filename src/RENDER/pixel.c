#include "../../includes/cub3d.h"

void    put_pixel(int x, int y, int color, t_data *data)
{
    if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || x < 0 || y < 0)
	{
        return;
	}
	if (!data->img->addr)
		return;
    int index = y * data->img->line_length + x * data->img->bits_per_pixel / 8;
    data->img->addr[index] = color & 0xFF;
    data->img->addr[index + 1] = (color >> 8) & 0xFF;
    data->img->addr[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_data *data)//map debug
{
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y, color, data);
    for(int i = 0; i < size; i++)
        put_pixel(x, y + i, color, data);
    for(int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, data);
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, data);

}

void clear_img(t_data *data)
{
    for(int i = 0; i < SCREEN_WIDTH; i++)
        for(int j = 0; j < SCREEN_HEIGHT; j++)
            put_pixel(i, j, 0x000000, data);
}

void    draw_map(t_data *data)//map debug
{
    for(size_t i = 0; i < data->map->height; i++)
        for(size_t j = 0; j < data->map->width; j++)
            if(data->map->map_array[i][j] == '1')
                draw_square(j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, 0x00FF00, data);
}

void draw_line(t_player *player, t_data *data, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->pos.x;
    float ray_y = player->pos.y;

	while (!touch(ray_x, ray_y, data))
	{	
		//printf("ray_x : %f\n ray_y : %f", ray_x, ray_y);		
		//put_pixel(ray_x, ray_y, 0xFF0000, data);//map debug
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	
    float dist = fixed_dist(player->pos.x, player->pos.y, ray_x, ray_y, data);
    float height = (BLOCK_SIZE / dist) * (SCREEN_WIDTH / 2);
    int start_y = (SCREEN_HEIGHT - height) / 2;
    int end = start_y + height;
    while (start_y < end)
    {
        put_pixel(i, start_y, 255, data);
        start_y++;
    } 
}