#include "../../includes/cub3d.h"

static void trim_spaces(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	if (!str) // str NULL ise hata ver veya bir şey yapmadan dön
	{
        printf("Error: trim_spaces received a NULL pointer.\n");
		return ;
	}
	// Başlangıçtaki boşlukları kaldır
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	// Fazladan boşlukları kaldır ve stringi sıkıştır
	while (i < len)
	{
		if (str[i] != ' ' && str[i] != '\t')
			str[j++] = str[i];
		else if (j > 0 && str[j - 1] != ' ') // Birden fazla boşluk varsa tekine indir
			str[j++] = ' ';
		i++;
	}
	// Sona kalan fazladan boşlukları kaldır
	if (j > 0 && str[j - 1] == ' ')
		j--;
	str[j] = '\0'; // Stringin sonunu belirle
}

static int	init_texture(int i, t_data *data, char *path)
{
	int		size;
	char	*texture;
	t_img	*img;

	size = 64;
	data->texture.xpm[i] = (t_img *)malloc(sizeof(t_img));
	img = data->texture.xpm[i];
	texture = ft_strndup(path, ft_strlen(path));
	if (texture[ft_strlen(texture) - 1] == '\n')
		texture[ft_strlen(texture) - 1] = '\0';
	img->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, texture, &size, &size);
	if (!img->img_ptr)
		return (0);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		return (0);
	if (texture)
		free(texture);
	return (1);
}

static int	get_color(t_data *data, char *path)
{
	int		i;
	int		color;
	char	**rgb;

	i = 0;
	rgb = ft_split(path, ',');
	if (!rgb)
		return (printf("Error: Invalid color format!\n"), 1);
	while (rgb[i])
		i++;
	if (i != 3)
		return (printf("Error: Invalid color format!\n"), 1);
	color = ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]);
	if (color < 0)
		return (printf("Error: Invalid color format!\n"), 1);
	if (!ft_strncmp(path, "F ", 2))
		data->texture.bottom = color;
	else
		data->texture.top = color;
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
	return (0);
}

static int	check_format(t_data *data, char *path)
{
	if (!ft_strncmp(path, "NO ", 3))
	{
		if (!init_texture(NORTH, data, path + 3))
			return (printf("Error: Invalid NO texture path!\n"), 1);
	}
	else if (!ft_strncmp(path, "SO ", 3))
	{
		if (!init_texture(SOUTH, data, path + 3))
			return (printf("Error: Invalid SO texture path!\n"), 1);
	}
	else if (!ft_strncmp(path, "WE ", 3))
	{
		if (!init_texture(WEST, data, path + 3))
			return (printf("Error: Invalid WE texture path!\n"), 1);
	}
	else if (!ft_strncmp(path, "EA ", 3))
	{
		if (!init_texture(EAST, data, path + 3))
			return (printf("Error: Invalid EA texture path!\n"), 1);
	}
	else if (!ft_strncmp(path, "F ", 2) || !ft_strncmp(path, "C ", 2))
		return (get_color(data, path));
	else
		return (printf("Error: Invalid texture format!\n"), 1);
	return (0);
}

int	create_textures(t_data *data, char *path)
{
	trim_spaces(path);
	if (!ft_strncmp(path, "\n", 1))
		return (0);
	if (check_format(data, path))
		return (1);
	return (0);
}
