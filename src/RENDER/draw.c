#include "../../includes/cub3d.h"

static t_raycast	init_ray(t_data *data)
{
	t_raycast	ray;

	ray.pos.x = data->player->pos.x;
	ray.pos.y = data->player->pos.y;
	ray.dir.x = data->player->dir.x;
	ray.dir.y = data->player->dir.y;
	ray.plane.x = data->player->plane.x;
	ray.plane.y = data->player->plane.y;
	return (ray);
}

/*
	Eğer bu satırlar olmasaydı ne olurdu görmek için bittikten sonra DENE!!!!!!!
*/
static void	draw_wall(t_raycast *ray, t_data *data, int i)
{
	ray->draw.wall_x -= floor(ray->draw.wall_x); //Texture'ın hangi konumda başlayacağını belirler. (Örneğin 3.5 bir duvara çarptıysak texture 0.5 konumunda başlayacak. Duvarı 1'e 1'lik bir texutre ile kaplarsak 0.5'ten başlayarak 1'e kadar olan kısmı duvara çizeriz. Çünkü diğer türlü texture yanlış çizilir.)
	ray->draw.tex.x = (int)(ray->draw.wall_x * (double)64); //Texture 64x64 olduğu için başlangıç pixelini 64 ile çarparız. Bu sayede textureda doğru konumundan çizmeye başlarız.
	 if ((ray->raydir.x < 0 && ray->horizontal == 0) || (ray->raydir.y > 0 && ray->horizontal == 1)) //Eğer duvar x ekseninde bir duvar ise ve rayin x yönündeki hareketi pozitifse dokuyu tersten çizmemiz gerekir.
		ray->draw.tex.x = 64 - ray->draw.tex.x - 1; //Bu yüzden texture'ı tersten çizmek için texture'ın başlangıç pixelini 64'ten çıkarırız.
	ray->draw.step = 1.0 * 64 / ray->draw.line_height; //Duvarın yüksekliğine göre texture'ın çizilme adımını belirler. (Duvar büyükse pixelleri daha büyük çizmemiz gerekir, küçükse daha küçük çizmemiz gerekir.)
	ray->draw.tex_pos = (ray->draw.start.x - SCREEN_HEIGHT / 2 + ray->draw.line_height / 2) * ray->draw.step; //Texture'ın çizilmeye başlanacağı yeri ekranın ve çizginin tam ortasından olması gerektiğini belirtir. Öbür türlü texturelar yamuk gözükür.
	fill_texture(ray, data, i); //Texture'ı çizer.
}

static t_raycast	init_ray2(t_raycast *ray, int i)
{
	double		camera_x;
	
	camera_x = 2 * i / (double)SCREEN_WIDTH - 1; //Bu değişken ekrandaki her pixel için hesaplanır. Rayin hangi yönde çizileceğini belirler. -1 ve 1 arasında değer alır.
	ray->raydir.x = ray->dir.x + ray->plane.x * camera_x; //Oyuncunun düzlemini hangi pixelde ise onunla çarpıp oyuncunun yönüne ekliyor. Bu sayede rayin hangi yönde çizilceği belirleniyor.
	ray->raydir.y = ray->dir.y + ray->plane.y * camera_x; //Aynı işlem y için uygulanıyor.
	ray->map.x = (int)ray->pos.x; //Rayin haritadaki MUTLAK x konumu(Yani ray_pos.x 1.5 ise ray_map.x 1 olur)
	ray->map.y = (int)ray->pos.y; //Rayin haritadaki MUTLAK y konumu(Yani ray_pos.y 1.5 ise ray_map.y 1 olur)
	/*
		Delta distance rayin x ve y yönündeki hareketine göre 1 birim hareket ettiğinde haritadaki bir kareyi ne kadar hareket ettiğini gösterir. 
		Bu değerler rayin haritadaki bir kareyi geçtiğinde ne kadar hareket ettiğini gösterir.(Dik üçgen çiz, x'i bir birim arttır, ve hipotenüsün
		ne olduğunu hesapla. 1/cos(teta) çıkacak. Bizim buradaki cos(teta) değerimiz rayin x yönündeki hareketi. Bu yüzden 1/raydir.x olacak)
	*/
	ray->deltadist.x = fabs(1 / ray->raydir.x);
	ray->deltadist.y = fabs(1 / ray->raydir.y);
	ray = calc_sidedist(ray);
	ray->hit = 0;
	return (*ray);
}

static void	raycast(t_data *data)
{
	int			i;
	t_raycast	ray;

	i = -1;
	ray = init_ray(data);
	while (++i < SCREEN_WIDTH)
	{
		ray = init_ray2(&ray, i);
		ray = create_ray(&ray, data);
		ray = calc_ray_len(&ray, data);
		draw_wall(&ray, data, i);
	}
}

void	draw(t_data *data)
{
	raycast(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0, 0);
}