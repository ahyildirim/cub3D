#include "../../includes/cub3d.h"

char	*ft_strndup(char *str, size_t n)
{
	char	*dup;
	size_t	i;

	if (ft_strlen(str) < n)
		n = ft_strlen(str);
	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}