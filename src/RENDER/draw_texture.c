#include "../../includes/cub3d.h"

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) //Eğer pixel ekrandan dışarıda kalıyorsa fonksiyonu sonlandırırız.
		return ;
	if (!img->addr)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)); //Koyduğumuz pixelin tam ve kesin adresini belirler(Adresin başlangıcı + (y * satır uzunluğu + x * pixelin bit uzunluğu / 8)) -> (satır uzunluğu = ekran genişliği * 4)
	*(unsigned int *)dst = color; //Bu adresin içine color değerini atarız.
}

static int	get_color(t_img *img, int x, int y)
{
	return (*(size_t *)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)))); //Texture'dan alınan rengi belirler.
}

void fill_texture(t_raycast *ray, t_data *data, int i)
{
	size_t	y; //mlx fonksiyonu size_t istiyor.
	t_img	*tmp;

	tmp = data->texture.xpm[ray->draw.wall]; //Hangi texture'ı kullanacağımızı belirler.
	y = -1;
	while(++y < SCREEN_HEIGHT)
	{
		if (y < (size_t)ray->draw.start.x) //Duvarın çizilmeye başlancağı yükseklikten yukarıdaysak tavanı çizeriz(Mantıken duvarın üstünü tavan olarak görmemiz gerekir)
			put_pixel(data->img, i, y, data->texture.top);
		else if (y < (size_t)ray->draw.start.y) //Duvarın çizilmeye başlanacağı sınırlar içerisindeysek duvarı çizmeye başlarız.
		{
			ray->draw.tex.y = (int)ray->draw.tex_pos % 64; //Texture'ın 0-63 sınırları arasında kalmasını sağlar. (Texture 64x64 olduğu için 64'e modunu alırız)
			ray->draw.tex_pos += ray->draw.step; //Çizgi uzunluğuna göre hesapladığımız step kadar texture'ın pozisyonunu güncelleriz.
			ray->draw.color = get_color(tmp, ray->draw.tex.x, ray->draw.tex.y); //Texture'dan alınan rengi belirler.
			put_pixel(data->img, i, y, ray->draw.color); //Texture'dan alınan rengi çizer.
		}
		else
			put_pixel(data->img, i, y, data->texture.bottom); //Duvarın çizilmeye başlanacağı yükseklikten aşağıdaysak zemini çizeriz(Mantıken duvarın altını zemin olarak görmemiz gerekir)
	}
}