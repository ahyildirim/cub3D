#include "../../includes/cub3d.h"

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
		tmp = (char *)malloc(width + 1);
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