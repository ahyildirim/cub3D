#include "../../includes/cub3d.h"
/*
	Yatay olarak duvardan önce 0NSWE karakterlerinden biri gelemeyeceği için bunun kontrolü
	ve boşluk karakteri var ise bundan önce 0NSWE karakterleri gelemeyeceği için bunun kontrolü
	yapılır. Flag duvardan sonra olup olmadığının kontrolünü sağlamak için.
*/

static int	check_horizontal(char **map, int i, int j, int flag)
{
	while (map[++i])
	{
		flag = 0;
		j = -1;
		while (map[i][++j])
		{
			if (flag == 0 && map[i][j] == '1')
				flag ^= 1;
			if (flag == 0 && ft_strchr("NSEW0", map[i][j]))
				return (0);
			if (flag == 1 && map[i][j] == ' ')
			{
				if (map[i][j - 1] && ft_strchr("0NSEW", map[i][j - 1]))
					return (0);
				flag ^= 1;
			}
		}
	}
	return (1);
}

/*
	Yatay ile aynı mantıkta bu sefer dikey bir şekilde kontrol ediyoruz.
*/

static int	check_vertical(char **map, int i, int j, int flag)
{
	while (map[0][++j])
	{
		flag = 0;
		i = 0;
		while (map[i] && map[i][j])
		{
			if (flag == 0 && map[i][j] == '1')
				flag ^= 1;
			if (flag == 0 && ft_strchr("NSEW0", map[i][j]))
				return (0);
			if (flag == 1 && map[i][j] == ' ')
			{
				if (map[i - 1] && map[i - 1][j]
						&& ft_strchr("0NSEW", map[i - 1][j]))
					return (0);
				flag ^= 1;
			}
			if (!map[i + 1] && ft_strchr("NSEW0", map[i][j]))
				return (0);
			i++;
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