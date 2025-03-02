#include "../../includes/cub3d.h"

int	ft_countwords(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			return (count);
		while (*s && *s != c)
			s++;
		count++;
	}
	return (count);
}

int	ft_countchars(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c)
{
	char	**str;
	int		len;

	len = 0;
	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!str)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		str[len++] = ft_substr(s, 0, ft_countchars(s, c));
		s += ft_countchars(s, c);
	}
	str[len] = NULL;
	return (str);
}
