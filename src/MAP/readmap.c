#include "../../includes/cub3d.h"
/*
	Mapin uzantısı .cub kontrolünü sağlıyoruz.
*/

static int	check_extension(char *av)
{
	size_t	len;
	char **str;
	int i;

	i = 0;
	str = ft_split(av, '/');
	while (str[i])
		i++;
	if (ft_strlen(str[i - 1]) < 5)
	{
		free_arr(str);
		return (0);
	}
	len = ft_strlen(av) - 4;
	if (ft_strcmp(av + len, ".cub"))
	{
		free_arr(str);
		return (1);
	}
	free_arr(str);
	return (0);
}

/*
	Mapi daha sonrasında splitle ayırmaya hazır hale getirmek için önce tüm içeriği
	tek bir satır halinde okuyoruz.
*/

static char	*read_map_text(int fd)
{
	char	*str;
	char	*tmp;
	char    *result;

	tmp = 0;
	while (1) //Map'den önce istenildiği kadar newline atılabileceği için önce bu newline'ları geçmek için bir döngü.
	{
		if (tmp)
			free(tmp);
		tmp = get_next_line(fd);
		if (!tmp || ft_strncmp(tmp, "\n", 1))
			break;
	}
	str = 0;
	while (tmp) //Ardından mapi tek tek okuyup tüm hepsini birleştiren kod.
	{
		str = ft_strjoin(str, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (!str)
		return (NULL);
	result = ft_strdup(str); // Yeni: Temiz bir kopya oluştur
	free(str);               // Yeni: Orijinal string'i temizle
	return (result);
}

/*
	Mapin içeriğini okuyup döndürüyoruz.
*/

static char	**read_map(t_data *data, int fd)
{
	size_t	tmp_width;
	char	**map;
	char	*map_text;
	char	*double_newline;

	map_text = read_map_text(fd); //Tüm içerği al.
	if (!map_text)
		return (0);
	double_newline = ft_strnstr(map_text, "\n\n1", ft_strlen(map_text)); //Eğer map texti içinde iki adet newline varsa hatalıdır. Bunu kontrol et.
	if (double_newline)
		return (free(map_text), NULL);
	map = ft_split(map_text, '\n'); //Split ile mapi \n itibari ile böl.
	free(map_text);
	data->map->height = 0;
	data->map->width = 0;
	while(map[data->map->height]) //Uzunluk ve genişlik hesabı yap. En geniş satırı baz al.
	{
		tmp_width = ft_strlen(map[data->map->height]);
		if (data->map->width < tmp_width)
			data->map->width = tmp_width + 1; //Neden +1?
		data->map->height++;
	}
	return (map);
}

int	load_sprites(int fd, t_data *data)
{
	char *sprite_path;

	sprite_path = NULL;
	while (1)
	{
		sprite_path = get_next_line(fd);
		if (create_textures(data, sprite_path)) //Sprite'ları yükleme.
		{
			free(sprite_path);
			end_gnl(fd);
			return (0);
		}
		free(sprite_path);
		if (data->texture.bottom != -1 && data->texture.top != -1 && 
			data->texture.xpm[0] && data->texture.xpm[1] && data->texture.xpm[2] && data->texture.xpm[3])
			break;
	}
	if (data->texture.bottom == -1 || data->texture.top == -1)
		return (0);
	return (1);
}

/*
	Mapin gerekli kontrollerini yapıp mapi oluşturuyoruz.
*/

int	create_map(t_data *data, char *map_name)
{
	int	fd;

	data->map = (t_map *)malloc(sizeof(t_map));
	if (ft_strlen(map_name) < 5 || !check_extension(map_name)) //Sadece .cub isimli dosya veya .cub uzantısı olmayan dosya kontrolü.
		return (error_free("Wrong file format! Usage: map_name.cub", data, 0));
	fd = open(map_name, O_RDONLY); //Dosyayı açma.
	if (fd < 0)
		return (error_free("File not found!", data, 0));
	if (!load_sprites(fd, data)) //Sprite'ları yükleme.
		return (error_free("An error occured while loading sprites.", data, 1));
	data->map->map_array = read_map(data, fd); //Dosyanın içeriğini okuma.
	if (!data->map->map_array)
		return (error_free("An error occured while reading map.", data, 2));
	if (!normalize_map(data->map->map_array, data->map->width))
		return (error_free("Invalid characters found!", data, 2));
	if (!check_map(data->map->map_array))
		return (error_free("Map must be covered with walls!", data ,2));
	close(fd);
	return (1);
}
