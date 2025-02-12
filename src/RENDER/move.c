#include "../../includes/cub3d.h"

void    rotate_move(t_data *data, float angle_speed)
{
    if (data->player->l_rotate)
        data->player->angle -= angle_speed;
    if (data->player->r_rotate)
        data->player->angle += angle_speed;
    if (data->player->angle > 2 * PI)
        data->player->angle = 0;
    if (data->player->angle < 0)
        data->player->angle = 2 * PI;
}

void move_player(t_data *data)
{
    int speed = 3;
    float   angle_speed = 0.03;
    float   cos_angle = cos(data->player->angle);
    float   sin_angle = sin(data->player->angle);
    rotate_move(data, angle_speed);
    if (data->onkey.key_w)
    {
        if (!touch(data->player->pos.x + cos_angle * speed, data->player->pos.y + sin_angle * speed, data))
        {
            data->player->pos.x += cos_angle * speed;
            data->player->pos.y += sin_angle * speed;
        }
    }
    if (data->onkey.key_s)
    {
        if (!touch(data->player->pos.x - cos_angle * speed, data->player->pos.y - sin_angle * speed, data))
        {
            data->player->pos.x -= cos_angle * speed;
            data->player->pos.y -= sin_angle * speed;
        }
    }
    if (data->onkey.key_a)
    {
        if (!touch(data->player->pos.x + cos_angle * speed, data->player->pos.y - sin_angle * speed, data))
        {
            data->player->pos.x += cos_angle * speed;
            data->player->pos.y -= sin_angle * speed;
        }
    }
    if (data->onkey.key_d)
    {
        if (!touch(data->player->pos.x - cos_angle * speed, data->player->pos.y + sin_angle * speed, data))
        {
            data->player->pos.x -= cos_angle * speed;
            data->player->pos.y += sin_angle * speed;
        }
    }
}