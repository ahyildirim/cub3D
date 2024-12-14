#include "../../includes/cub3d.h"

char	*ft_strchr(char *s, int c)
{
	if (*s == (char)c)
		return ((char *)s);
	while (*s++)
		if (*s == (char)c)
			return ((char *)s);
	return (0);
}