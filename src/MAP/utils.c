#include "../../includes/cub3d.h"

void trim_spaces(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	if (!str) // str NULL ise hata ver veya bir şey yapmadan dön
		return ;
	// Başlangıçtaki boşlukları kaldır
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	// Fazladan boşlukları kaldır ve stringi sıkıştır
	while (i < len)
	{
		if (str[i] != ' ' && str[i] != '\t')
			str[j++] = str[i];
		else if (j > 0 && (str[j - 1] != ' ' && str[j - 1] != '\t')) // Birden fazla boşluk varsa tekine indir
			str[j++] = ' ';
		i++;
	}
	// Sona kalan fazladan boşlukları kaldır
	if (j > 0 && (str[j - 1] == ' ' || str[j - 1] == '\t'))
		j--;
	str[j] = '\0'; // Stringin sonunu belirle
}

void clear_newline(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while(i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i--;
	str[i + 1] = '\0';
}

void	end_gnl(int fd)
{
	char *tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}
