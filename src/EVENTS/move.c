#include "../../includes/cub3d.h"

static double calc_dist(double pos)
{
	return (pos * MOVESPEED * MV);
}

/*
	Döndürme fonksiyonu karakterin yönünü ve düzlemini ROTATESPEED değişkenine göre döndürür. Buradaki hesaplamalar dönüş matrisi kullanılarak yapılır.
	Dönüş matrisi şu şekildedir(bknz. https://www.muhendisbeyinler.net/donme-matrisi-nedir-rotation-matrix/): 
	| yeni_x |	=	| cos(ROTATESPEED) -sin(ROTATESPEED) | * | eski_x |
	| yeni_y |	=	| sin(ROTATESPEED)  cos(ROTATESPEED) | * | eski_y |

	Lineer cebirden hatırlarsak formül şu şekilde çıkar: yeni_x = eski_x * cos(ROTATESPEED) - eski_y * sin(ROTATESPEED)
														yeni_y = eski_x * sin(ROTATESPEED) + eski_y * cos(ROTATESPEED)
	Bu işlemleri yaparak hem düzlemini hem de yönünü döndürmüş oluyoruz.
*/

static void rotate(t_data *data)
{
	double old_dir_x;
	double old_plane_x;

	old_plane_x = data->player->plane.x;
	old_dir_x = data->player->dir.x;
	if (data->onkey.key_left)
	{
		data->player->dir.x = data->player->dir.x * cos(-ROTATESPEED) - data->player->dir.y * sin(-ROTATESPEED);
		data->player->dir.y = old_dir_x * sin(-ROTATESPEED) + data->player->dir.y * cos(-ROTATESPEED);
		data->player->plane.x = data->player->plane.x * cos(-ROTATESPEED) - data->player->plane.y * sin(-ROTATESPEED);
		data->player->plane.y = old_plane_x * sin(-ROTATESPEED) + data->player->plane.y * cos(-ROTATESPEED);
	}
	if (data->onkey.key_right)
	{
		data->player->dir.x = data->player->dir.x * cos(ROTATESPEED) - data->player->dir.y * sin(ROTATESPEED);
		data->player->dir.y = old_dir_x * sin(ROTATESPEED) + data->player->dir.y * cos(ROTATESPEED);
		data->player->plane.x = data->player->plane.x * cos(ROTATESPEED) - data->player->plane.y * sin(ROTATESPEED);
		data->player->plane.y = old_plane_x * sin(ROTATESPEED) + data->player->plane.y * cos(ROTATESPEED);
	}
}

/*
	Karakterimizin girilen yönünü veya düzlemini alıyor(W ve S basıldıysa yön, A ve D basıldıysa düzlem). Buna göre karakterin önce yeni konumunu hesaplıyor
	ve daha sonra bu konumun haritada hareket edilebilen bir yer olup olmadığını kontrol ediyor. Eğer hareket edilebilen bir yerse karakterin konumunu 
	güncelliyor. Hesaplama ise şu şeklide yapılıyor: Karakterin konumu (+ veya -) (yön veya düzlem * hız * çarpan). Örneğin karakterimiz kuzeye
	bakarak başlasın ve haritadaki konumu (1,5, 1,5 olsun). Bu durumda karakterin yönü (0, -1) ve düzlemi (0.66, 0). Eğer W Basılırsa karakterin yeni konumu
	1,5 + (1,5 * 3 * 0,1) olacak. Yani 1,95. Şimdi bunu integera çevirdiğimizde 1 olur. Map[1][1]'e bakıp bu konumda 0 olduğu için karakterin konumu 
	güncellenebilir derdik. Fakat movespeed 3 değil de 4 olsaydı Map[1][2]'ye bakacaktık ve eğer bu konumda 1 olsaydı karakter konumu güncellenmeyecekti.
*/

static void set_position(t_data *data, double x, double y, char sign)
{
	if (sign == '+')
	{
		if (!data->map->map_array[(int)(data->player->pos.y + calc_dist(y))])
			return;
		if (ft_strchr("1", data->map->map_array[(int)(data->player->pos.y + calc_dist(y))][(int)(data->player->pos.x + calc_dist(x))]))
			return;
		data->player->pos.y += calc_dist(y);
		data->player->pos.x += calc_dist(x);
	}
	else if (sign == '-')
	{
		if (!data->map->map_array[(int)(data->player->pos.y - calc_dist(y))])
			return;
		if (ft_strchr("1", data->map->map_array[(int)(data->player->pos.y - calc_dist(y))][(int)(data->player->pos.x - calc_dist(x))]))
			return;
		data->player->pos.y -= calc_dist(y);
		data->player->pos.x -= calc_dist(x);
	}
}

int move(t_data *data)
{
	if (data->onkey.key_w)
		set_position(data, data->player->dir.x, data->player->dir.y, '+');
	if (data->onkey.key_s)
		set_position(data, data->player->dir.x, data->player->dir.y, '-');
	if (data->onkey.key_a)
		set_position(data, data->player->plane.x, data->player->plane.y, '-');
	if (data->onkey.key_d)
		set_position(data, data->player->plane.x, data->player->plane.y, '+');
	if (data->onkey.key_left || data->onkey.key_right)
		rotate(data);
	if (data->onkey.key_w || data->onkey.key_s || data->onkey.key_a || data->onkey.key_d || data->onkey.key_left || data->onkey.key_right)
		return (1);
	else
		return (0);
}