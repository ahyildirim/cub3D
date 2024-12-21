#include "../../includes/cub3d.h"

int key_down(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		quit_game(data);
	else if (keycode == XK_w)
		data->onkey.key_w = 1;
	else if (keycode == XK_a)
		data->onkey.key_a = 1;
	else if (keycode == XK_s)
		data->onkey.key_s = 1;
	else if (keycode == XK_d)
		data->onkey.key_d = 1;
	else if (keycode == XK_Up)
		data->onkey.key_up = 1;
	else if (keycode == XK_Down)
		data->onkey.key_down = 1;
	else if (keycode == XK_Left)
		data->onkey.key_left = 1;
	else if (keycode == XK_Right)
		data->onkey.key_right = 1;
	return (0);
}
int key_up(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		quit_game(data);
	else if (keycode == XK_w)
		data->onkey.key_w = 1;
	else if (keycode == XK_a)
		data->onkey.key_a = 1;
	else if (keycode == XK_s)
		data->onkey.key_s = 1;
	else if (keycode == XK_d)
		data->onkey.key_d = 1;
	else if (keycode == XK_Up)
		data->onkey.key_up = 1;
	else if (keycode == XK_Down)
		data->onkey.key_down = 1;
	else if (keycode == XK_Left)
		data->onkey.key_left = 1;
	else if (keycode == XK_Right)
		data->onkey.key_right = 1;
	return (0);
}