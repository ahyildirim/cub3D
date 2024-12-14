#include "../../includes/cub3d.h"

char	*ft_strdup(char *s)
{
	char	*str;
	size_t	i;

	i = -1;
	str = (char *) malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	while (s[++i])
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}