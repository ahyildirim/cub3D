#include "../../includes/cub3d.h"

bool touch(float px, float py, t_data *data)
{
    int x = (int)(px / BLOCK_SIZE);
    int y = (int)(py / BLOCK_SIZE);
        
    if (data->map->map_array[y][x] == '1')
        return true;
    return false;
}

float distance(float x, float y)
{
    return sqrt(x * x + y * y);
}
float fixed_dist(float x1, float y1, float x2, float y2, t_data *data)
{
    float   delta_x = x2 - x1;
    float   delta_y = y2 - y1;
    float   angle = atan2(delta_y, delta_x) - data->player->angle;
    float   fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

int render_frame(t_data *data)
{
    move_player(data);
    clear_img(data);
    //draw_map(data);//map debug
    //draw_square(data->player->pos.x, data->player->pos.y, 10, 0x00FF00, data); //map debug

    float fraction = PI / 3 / SCREEN_WIDTH;
    float start_x = data->player->angle - PI / 6;
    int i = 0;
    while (i < SCREEN_WIDTH)
    {
        draw_line(data->player, data, start_x, i);
        start_x += fraction;
        i++;
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0, 0);
    //printf("pos x : %f\npos y : %f\n", data->player->pos.x / BLOCK_SIZE, data->player->pos.y / BLOCK_SIZE);
    //printf("map h : %zu\n map w: %zu", data->map->height,data->map->width);
    //mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
    return (0);
}