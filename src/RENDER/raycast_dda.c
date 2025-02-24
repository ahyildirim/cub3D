#include "../../includes/cub3d.h"

static double	get_perp_wall_dist(t_raycast *ray)
{
	if (ray->horizontal == 0)
		return (ray->sidedist.x - ray->deltadist.x);
	else
		return (ray->sidedist.y - ray->deltadist.y);
}

static t_raycast	set_wall(t_raycast *ray, t_data *data)
{
	if (ray->horizontal == 0) //Eğer yataydaki bir duvar çarptıysak
	{
		ray->draw.wall_x = data->player->pos.y + ray->draw.perp_wall_dist * ray->raydir.y; //Texture işlemek için duvarın tam olarak hangi konumunda ışının çarptığını hesaplar.(Oyuncunun mevcut y konumu + rayin duvara olan dik uzaklığı * rayin y yönündeki hareketi)
		if (ray->map.x < data->player->pos.x) //Işının çarptığı duvarın sol mu sağ mı olduğunu belirler, eğer oyuncunun solundaysa sol duvar için flag atar.
			ray->draw.wall = WEST; //Bu durumda sol duvar flagi 3.
		else //Eğer oyuncunun sağında ise sağ duvar için flag atar.
			ray->draw.wall = EAST; //Bu durumda sağ duvar flagi 2.
	}
	else //Eğer dikeydeki bir duvara çarptıysak
	{
		ray->draw.wall_x = data->player->pos.x + ray->draw.perp_wall_dist * ray->raydir.x; //Texture işlemek için duvarın tam olarak hangi konumunda ışının çarptığını hesaplar.(Oyuncunun mevcut x konumu + rayin duvara olan dik uzaklığı * rayin x yönündeki hareketi)
		if (ray->map.y < data->player->pos.y) //Işının çarptığı duvarın üst mü alt mı olduğunu belirler, eğer oyuncunun üstündeyse üst duvar için flag atar.
			ray->draw.wall = NORTH; //Bu durumda üst duvar flagi 1.
		else //Eğer oyuncunun altındaysa alt duvar için flag atar.
			ray->draw.wall = SOUTH; //Bu durumda alt duvar flagi 0.
	}
	return (*ray);
}

t_raycast	create_ray(t_raycast *ray, t_data *data)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y) //(x < y olduğu için x yönünde ray hareket eder)
		{
			ray->map.x += ray->step.x; //Rayin haritadaki mutlak konumunu ne tarafa doğru hareket ettiysek ona göre güncelliyoruz. Bu durumda x < y olduğu için x'e doğru hareket ederiz. Bu sebeple x'e attığımız adımı ekleriz.
			ray->sidedist.x += ray->deltadist.x; //Rayin bir sonraki dikey çizgiye olan mesafesini günceller. Yani eski mesafeye x ekseninde bir birimde ne kadar ilerlediğimizi ekleriz.
			ray->horizontal = 0; //Rayin yatay mı dikey mi olduğunu belirler. Bu durumda ray yatay olduğu için 0 olur.
		}
		else //(y < x olduğu için y yönünde ray hareket eder)
		{
			ray->map.y += ray->step.y; //Aynı işlem y için de geçerli. Bu durumda y < x olduğu için y'e doğru hareket ederiz. Bu sebeple y'e attığımız adımı ekleriz.
			ray->sidedist.y += ray->deltadist.y; //Aynı işlem y için de geçerli. Bu durumda rayin bir sonraki yatay çizgiye olan mesafesini günceller. Yani eski mesafeye y ekseninde bir birimde ne kadar ilerlediğimizi ekleriz.
			ray->horizontal = 1; //Aynı işlem y için de geçerli. Bu durumda ray dikey olduğu için 1 olur.
		}
		if (!data->map->map_array[ray->map.y]) //Eğer rayin haritadaki y konumu haritanın yüksekliğinden büyükse döngüyü kırarız.
			break ;
		else if (data->map->map_array[ray->map.y][ray->map.x] == '1') //Eğer rayin haritadaki konumunda 1(duvar) varsa duvara çarptığımızı belirtiriz.
			ray->hit = 1;
	}
	return (*ray);
}

t_raycast	calc_ray_len(t_raycast *ray, t_data *data)
{
	ray->draw.perp_wall_dist = get_perp_wall_dist(ray); //Rayin duvara olan dik uzaklığını hesaplar.
	ray->draw.line_height = (int)(SCREEN_HEIGHT / ray->draw.perp_wall_dist); //Rayin duvara olan dik uzaklığına göre duvarın yüksekliğini hesaplar. Bu sayede duvardan ne kadar uzaklaşırsak duvar o kadar küçük, ne kadar yaklaşırsak o kadar büyük gözükür.
	ray->draw.start.x = -ray->draw.line_height / 2 + SCREEN_HEIGHT / 2; //Duvarın çizilmeye başlanacağı yeri belirler.
	if (ray->draw.start.x < 0) //Eğer duvarın çizilmeye başlanacağı yer ekrandan dışarıda kalıyorsa 0 yaparız.
		ray->draw.start.x = 0;
	ray->draw.start.y = ray->draw.line_height / 2 + SCREEN_HEIGHT / 2; //Duvarın çizilmeye başlanacağı yüksekliği belirler.
	if (ray->draw.start.y >= SCREEN_HEIGHT) //Eğer duvarın çizilmeye başlanacağı yükseklik ekrandan dışarıda kalıyorsa ekrandan çıkacak şekilde ayarlarız.
		ray->draw.start.y = SCREEN_HEIGHT - 1;
	*ray = set_wall(ray, data); //Duvarın hangi tarafta olduğunu belirler.
	return (*ray);
}

t_raycast	*calc_sidedist(t_raycast *ray)
{
	if (ray->raydir.x < 0)
	{
		ray->step.x = -1; //Eğer rayin x yönündeki hareketi negatifse oyuncunun atacağı adım hep -1 olacak. Bu yüzden step.x -1 olacak.
		ray->sidedist.x = (ray->pos.x - ray->map.x) * ray->deltadist.x; //Rayin solundaki ilk kareye olan mesafe hesaplanıyor.
	}
	else
	{
		ray->step.x = 1; //Eğer rayin x yönündeki hareketi pozitifse oyuncunun atacağı adım hep 1 olacak. Bu yüzden step.x 1 olacak.
		ray->sidedist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->deltadist.x; //Rayin sağındaki ilk kareye olan mesafe hesaplanıyor. +1'in sebebi bulunduğumuz hücrenin bir sağındaki hücreye geçmek için 1 birim fazla almamız gerektiğini gösterir.
	}
	if (ray->raydir.y < 0)
	{
		ray->step.y = -1; //Aynı mantık y için de geçerli.
		ray->sidedist.y = (ray->pos.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1; //Aynı mantık y için de geçerli.
		ray->sidedist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->deltadist.y;
	}
	return (ray);
}
