#include "../../includes/cub3d.h"

#ifdef __APPLE__
    #define KEY_ESC 53
    #define KEY_W 13
    #define KEY_A 0
    #define KEY_S 1
    #define KEY_D 2
    #define KEY_UP 126
    #define KEY_DOWN 125
    #define KEY_LEFT 123
    #define KEY_RIGHT 124
#else
    #define KEY_ESC 65307
    #define KEY_W 119
    #define KEY_A 97
    #define KEY_S 115
    #define KEY_D 100
    #define KEY_UP 65362
    #define KEY_DOWN 65364
    #define KEY_LEFT 65361
    #define KEY_RIGHT 65363
#endif

int key_down(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		quit_game(data);
	else if (keycode == KEY_W)
		data->onkey.key_w = 1;
	else if (keycode == KEY_A)
		data->onkey.key_a = 1;
	else if (keycode == KEY_S)
		data->onkey.key_s = 1;
	else if (keycode == KEY_D)
		data->onkey.key_d = 1;
	else if (keycode == KEY_UP)
		data->onkey.key_up = 1;
	else if (keycode == KEY_DOWN)
		data->onkey.key_down = 1;
	else if (keycode == KEY_LEFT)
    {
        data->player->l_rotate = 1;
		data->onkey.key_left = 1;
    }
	else if (keycode == KEY_RIGHT)
    {
        data->player->r_rotate = 1;
		data->onkey.key_right = 1;
    }
	return (0);
}
int key_up(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
        quit_game(data);
    else if (keycode == KEY_W)
        data->onkey.key_w = 0;  // Changed from 1 to 0
    else if (keycode == KEY_A)
        data->onkey.key_a = 0;  // Changed from 1 to 0
    else if (keycode == KEY_S)
        data->onkey.key_s = 0;  // Changed from 1 to 0
    else if (keycode == KEY_D)
        data->onkey.key_d = 0;  // Changed from 1 to 0
    else if (keycode == KEY_UP)
        data->onkey.key_up = 0;  // Changed from 1 to 0
    else if (keycode == KEY_DOWN)
        data->onkey.key_down = 0;  // Changed from 1 to 0
    else if (keycode == KEY_LEFT)
    {
        data->player->l_rotate = 0;
		data->onkey.key_left = 0;
    }
	else if (keycode == KEY_RIGHT)
    {
        data->player->r_rotate = 0;
		data->onkey.key_right = 0;
    }  // Changed from 1 to 0
    return (0);
}