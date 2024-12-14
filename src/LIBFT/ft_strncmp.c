#include "../../includes/cub3d.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*xs1;
	unsigned char	*xs2;

	xs1 = (unsigned char *) s1;
	xs2 = (unsigned char *) s2;
	i = -1;
	while ((xs1[++i] || xs2[i]) && i < n)
		if (xs1[i] != xs2[i])
			return (xs1[i] - xs2[i]);
	return (0);
}
