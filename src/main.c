#include "../includes/cub3d.h"

/*
	Mapin uzantısı .cub kontrolünü sağlıyoruz.
*/

int	check_extension(char *av)
{
	size_t	len;

	len = ft_strlen(av) - 4;
	if (ft_strcmp(av + len, ".cub"))
		return (1);
	return (0);
}

/*
	Mapi daha sonrasında splitle ayırmaya hazır hale getirmek için önce tüm içeriği
	tek bir satır halinde okuyoruz.
*/

char	*read_map_text(int fd)
{
	char	*str;
	char	*tmp;

	tmp = NULL;
	while (1) //Map'den önce istenildiği kadar newline atılabileceği için önce bu newline'ları geçmek için bir döngü.
	{
		if (tmp)
			free(tmp);
		tmp = get_next_line(fd);
		if (ft_strncmp(tmp, "\n", 1))
			break ;
	}
	str = NULL;
	while (1) //Ardından mapi tek tek okuyup tüm hepsini birleştiren kod. Örneğin 111111\n10000001\n10000001\n11111111 gibi.
	{
		str = ft_strjoin(str, tmp);
		free(tmp);
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
	}
	return (str);
}

/*
	Mapin içeriğini okuyup döndürüyoruz.
*/

char	**read_map(t_data *data, int fd)
{
	size_t	tmp_width;
	char	**map;
	char	*map_text;
	char	*double_newline;

	map_text = read_map_text(fd); //Tüm içerği al.
	double_newline = ft_strnstr(map_text, "\n\n", ft_strlen(map_text)); //Eğer map texti içinde iki adet newline varsa hatalıdır. Bunu kontrol et.
	if (double_newline)
		return (0);
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

/*
	Yatay olarak duvardan önce 0NSWE karakterlerinden biri gelemeyeceği için bunun kontrolü
	ve boşluk karakteri var ise bundan önce 0NSWE karakterleri gelemeyeceği için bunun kontrolü
	yapılır. Flag duvardan sonra olup olmadığının kontrolünü sağlamak için.
*/

int	check_horizontal(char **map, int i, int j, int flag)
{
	while (map[++i])
	{
		j = -1;
		flag = 0;
		while (map[i][++j])
		{
			if (flag == 0 && map[i][j] == '1')
				flag ^= 1;
			if (flag == 0 && ft_strchr("0NSWE", map[i][j]))
				return (0);
			if (flag == 1 && map[i][j] == ' ')
			{
				if (map[i][j - 1] && ft_strchr("0NSWE", map[i][j - 1]))
					return (0);
				flag ^= 1;
			}
			if (!map[i][j + 1] && ft_strchr("0NSWE", map[i][j]))
				return (0);
		}
	}
	return (1);
}

/*
	Yatay ile aynı mantıkta bu sefer dikey bir şekilde kontrol ediyoruz.
*/

int check_vertical(char **map, int i, int j, int flag)
{
	while (map[0][++j])
	{
		flag = 0;
		i = -1;
		while (map[++i] && map[i][j])
		{
			if (flag == 0 && map[i][j] == '1')
				flag ^= 1;
			if (flag == 0 && ft_strchr("0NSWE", map[i][j]))
				return (0);
			if (flag == 1 && map[i][j] == ' ')
			{
				if (map[i - 1 ] && map[i - 1][j] && ft_strchr("0NSWE", map[i - 1][j]))
					return (0);
				flag ^= 1;
			}
			if (!map[i + 1] && ft_strchr("0NSWE", map[i][j]))
				return (0);
		}
	}
	return (1);
}

/*
	Map duvarlarla kaplı mı kontrolünü sağlıyoruz.
*/

int check_map(char **map)
{
	if (!check_horizontal(map, -1, -1, 0))
		return (0);
	if (!check_vertical(map, -1, -1, 0))
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
		return (printf("Wrong file format! Usage: map_name.cub\n"), 0);
	fd = open(map_name, O_RDONLY); //Dosyayı açma.
	if (fd < 0)
		return (printf("File not found: %s!\n", map_name), 0);
	data->map->map_array = read_map(data, fd); //Dosyanın içeriğini okuma.
	if (!data->map->map_array)
		return (printf("An error occured while reading map."), 0);
	if (!normalize_map(data->map->map_array, data->map->width))
		return (printf("Invalid characters found!"), 0);
	if (!check_map(data->map->map_array))
		return (printf("Map must be covered with walls!"), 0);
	close(fd);
	return (1);
}

int initialize(t_data *data, char **av)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	if (!create_map(data, av[1]))
		return (0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREEN_HEIGHT, SCREEN_WIDTH, "cub3d");
	if(!data->win_ptr)
		return (0);
	
}

int	main(int ac, char **argv)
{
	if (ac != 2)
		printf("Please insert a map!");
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	int x = create_map(data, argv[1]);
	printf("%d\n", x);
}
