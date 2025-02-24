#include "../../includes/cub3d.h"

static void	ft_bzero(void *s, size_t n)
{
	while (n-- > 0)
	{
		*((unsigned char *)s) = 0;
		s++;
	}
}

static void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	ret = (void *)malloc(nmemb * size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, nmemb * size);
	return (ret);
}

/*
	Mapin işlemesini daha kolay hale getirmek için mapde hiçbir şey bulunmayan yerlere boşluk veriyoruz.
	Eğer bunu yapmazsak ileride map kontrolü yaparken işimiz zorlaşır. Kısacası so_longtaki gibi mapi dikdörtgen
	haline getiriyoruz.
	Ayrıca geçersiz karakter kontrolü yapıyoruz.
*/

int normalize_map(char **map, int width)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (map[++i])
	{
		tmp = ft_calloc(width + 1, sizeof(char));
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr("10NSE W", map[i][j]))
				return (0);
			tmp[j] = map[i][j];
		}
		while (++j < width)
			tmp = ft_strjoin(tmp, " ");
		free(map[i]);
		map[i] = tmp;
	}
	return (1);
}